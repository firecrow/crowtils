#!/usr/bin/env python2.7
import os, sys, md5, random, math
from subprocess import Popen, PIPE

camscwd = os.getcwd()
stg_path = camscwd + '/testing/stage'
fixture_path = camscwd + '/testing/fixtures/'

def test(is_pass, message, details=None):
  if is_pass:
    sys.stdout.write('.')
  else:
    print "failure: %s" % message
    if details:
      print details
    sys.exit(1)

# handle working directory
def cmd(*args, **kwargs):
  p = Popen(args, stderr=PIPE, stdout=PIPE)
  p.wait()
  return p

def strcmp(a, b):
  return md5.new(a).hexdigest() == md5.new(b).hexdigest()

# test removals 
#print
#c = cmd('./treetil', 'sort', '-a', 'orange', 'apple', 'bananna', 'carrot', 'delta', 'xzephyr', 'epsilon', 
#    '-x', 'notathing', '-x', 'apple', '-x', 'delta', '-x', 'xzephyr', '-x', 'epsilon')
#print c.stdout.read()
#print c.stderr.read()
#sys.exit(1)


## test alpha key output for balanced tree
c = cmd('./treetil', 'print', '-a', 'apple', 'bannana', 'carrot', 'delta', 'xzephyr', 'espilon')
with open('./testing/fixtures/alpha.treeprint.txt', 'r') as file:
  tp_out = c.stdout.read()
  print tp_out
  #test(strcmp(tp_out, file.read()), "comparing alpha treeprint output", tp_out)

# test integer key output for balanced tree
c = cmd('./treetil', 'print', '1', '4', '3', '5', '2', '7', '6')
with open('./testing/fixtures/int.treeprint.txt', 'r') as file:
  tp_out = c.stdout.read()
  print tp_out
  #test(strcmp(tp_out, file.read()), "comparing expected integer tree output", tp_out)

# test integer key with unset 
c = cmd('./treetil', 'print', '1', '10', '4', '11', '-x', '4', '3', '5', '2', '7', '6','-x', '3')
with open('./testing/fixtures/int.unset.treeprint.txt', 'r') as file:
  tp_out = c.stdout.read()
  print tp_out
  #test(strcmp(tp_out, file.read()), "comparing expected integer with unset tree output", tp_out)

# test unset root node alpha, with unset minmax flow
c = cmd('./treetil', 'print', '-a', 'Makefile', 'cams.c', 'cams.h', '-x', 'Makefile')
with open('./testing/fixtures/unset-alpha-root.txt', 'r') as file:
  tp_out = c.stdout.read()
  print tp_out
  #test(strcmp(tp_out, file.read()), "unsetting a root node whose value is the min, forcing unset_minmax to be called", tp_out)

# test unset root node alpha, with unset minmax flow
c = cmd('./treetil', 'join', '-a', 'Makefile', 'cams.c', 'cams.h')
with open('./testing/fixtures/join.txt', 'r') as file:
  tp_out = c.stdout.read()
  print tp_out
  #test(strcmp(tp_out, file.read()), "testing join functionality", tp_out)

# test tree sorting
def rand_char():
  code = int(math.ceil(random.random()*26))+97
  return chr(code)

def gen_alpha_values(amount, is_alpha=False):
  data = []
  count  = 0
  while count < amount:
    s = ""
    l = int(math.ceil(random.random()*count))
    for x in range(l+1):
      s += rand_char()
    if s not in data:
      data.append(s)
      count += 1
  return data

def gen_int_values(count, is_alpha=False):
  data = list(range(1, count+1))
  random.shuffle(data)
  data = map(lambda x: str(x), data)
  return data

def test_treesort(count, is_alpha=False):
  values = gen_alpha_values(count) if is_alpha else gen_int_values(count) 
  length = len(values)
  if is_alpha:
    #values.insert(0, "-v")
    values.insert(0, "-a")

  values.insert(0, 'print')
  values.insert(0, './treetil')

  c = cmd(*values)
  treeprint_res = c.stdout.read()

  values[1] = 'sort'
  c = cmd(*values)
  res = c.stdout.read()
  err = c.stderr.read()

  res_values = res.split('\n')[:-1]

  test(len(res_values) == length, "test length of sorted output matches number of elements, %d vs %d" % (len(res_values), length), treeprint_res)
  prev = res_values[0]
  for x in res_values[1:]:
    test(x > prev, "ensure each value is greater than the last", (x, treeprint_res))
    
# test sorting function of tree
#for i in range(1,101):
#  test_treesort(i)

for i in range(1,101):
  test_treesort(i, is_alpha=True)

print


