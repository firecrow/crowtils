int test_init(SuiteSet *set, void *data){
  int result;
  char *msg = dupstr("basic ct_tree_init results");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  if(tree->cmp == ct_cmp_alpha 
    && tree->free == NULL 
    && tree->balanced == true
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_set(SuiteSet *set, void *data){
  int result;
  int ret;
  char *msg = dupstr("result add");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};
  kv.key = dupstr("one");
  kv.data = dupstr("once");
  ret = ct_tree_set(tree, &kv);
  if(ret == CT_CREATED 
    && tree->len == 1
    && !tree->cmp(&(tree->min), &kv) 
    && !tree->cmp(&(tree->max), &kv) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_set_get(SuiteSet *set, void *data){
  int result;
  int ret;
  char *msg = dupstr("get result");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *one = dupstr("one");
  char *once = dupstr("once");

  kv.key = one;
  kv.data = once;
  ret = ct_tree_set(tree, &kv);

  kv.key = one;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);

  if(ret == CT_FOUND
    && !strcmp(kv.key, one) 
    && !strcmp(kv.data, once) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_set_unset(SuiteSet *set, void *data){
  int result;
  int ret;
  char *msg = dupstr("unset result");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *one = dupstr("one");
  char *once = dupstr("once");

  kv.key = one;
  kv.data = once;
  ret = ct_tree_set(tree, &kv);

  kv.key = one;
  kv.data = NULL;
  ret = ct_tree_unset(tree, &kv);
  ct_tree_next(tree, &kv);

  if(ret == CT_MODIFIED
    && tree->len == 0
    && tree->root == NULL
    && tree->is_void(&(tree->min))
    && tree->is_void(&(tree->max))
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int print3(SuiteSet *set, void *data){
  next(set, 0, NULL, data);
}

static SuiteSet *get_basic_set(){
  return set_init("basic", 4, test_init, test_set, test_set_get, test_set_unset);
}
