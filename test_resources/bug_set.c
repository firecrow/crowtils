int test_unset_root(SuiteSet *set, void *data){
  int result;
  int ret;
  int idx = 0;
  char *results[3];
  char *msg = dupstr("unset root in test");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *one = dupstr("one");
  char *once = dupstr("once");
  char *two = dupstr("two");
  char *twice = dupstr("twice");
  char *three = dupstr("three");
  char *thrice = dupstr("thrice");

  kv.key = one;
  kv.data = once;
  ret = ct_tree_set(tree, &kv);

  kv.key = two;
  kv.data = twice;
  ret = ct_tree_set(tree, &kv);

  kv.key = three;
  kv.data = thrice;
  ret = ct_tree_set(tree, &kv);

  kv.key = two;
  ret = ct_tree_unset(tree, &kv);
  if(tree->len == 2
    && !strcmp(tree->min.key, one)
    && !strcmp(tree->max.key, three)
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_unset_root_iter_prev(SuiteSet *set, void *data){
  int result;
  int ret;
  int idx = 0;
  char *results[3];
  char *msg = dupstr("unset root in test iter preivous");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *one = dupstr("one");
  char *once = dupstr("once");
  char *two = dupstr("two");
  char *twice = dupstr("twice");
  char *three = dupstr("three");
  char *thrice = dupstr("thrice");

  kv.key = one;
  kv.data = once;
  ret = ct_tree_set(tree, &kv);

  kv.key = two;
  kv.data = twice;
  ret = ct_tree_set(tree, &kv);

  kv.key = three;
  kv.data = thrice;
  ret = ct_tree_set(tree, &kv);

  kv.key = two;
  ret = ct_tree_unset(tree, &kv);

  kv.key = NULL;
  while(!ct_tree_previous(tree, &kv)){
    results[idx++] = kv.key;
  }
  
  if(tree->len == 2
    && !strcmp(tree->min.key, one)
    && !strcmp(tree->max.key, three)
    && !strcmp(results[0], three)
    && results[1] && !strcmp(results[1], one)
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

static SuiteSet *get_bug_set(){
  return set_init("bugs", 2, test_unset_root, test_unset_root_iter_prev);
}
