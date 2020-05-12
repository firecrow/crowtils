
int test_idx_set3_get3(SuiteSet *set, void *data){
  int result;
  int ret;
  char *results[3];
  char *msg = dupstr("set and get three result");
  struct ct_tree *tree = ct_tree_init(ct_cmp_idx, ct_is_void_idx, NULL);
  struct ct_leaf kv = {};

  char *one = dupstr("one");
  char *once = dupstr("once");
  char *two = dupstr("two");
  char *twice = dupstr("twice");
  char *three = dupstr("three");
  char *thrice = dupstr("thrice");

  kv.idx = 0;
  kv.data = once;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 1;
  kv.data = twice;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 2;
  kv.data = thrice;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 0;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);
  results[0] = kv.data;

  kv.idx = 1;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);
  results[1] = kv.data;

  kv.idx = 2;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);
  results[2] = kv.data;

  if(tree->len == 3
    && !strcmp(results[0], once) 
    && !strcmp(results[1], twice) 
    && !strcmp(results[2], thrice) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_idx_set3_unset2(SuiteSet *set, void *data){
  int result;
  int ret;
  char *msg = dupstr("set and unset three result");
  struct ct_tree *tree = ct_tree_init(ct_cmp_idx, ct_is_void_idx, NULL);
  struct ct_leaf kv = {};

  char *one = dupstr("one");
  char *once = dupstr("once");
  char *two = dupstr("two");
  char *twice = dupstr("twice");
  char *three = dupstr("three");
  char *thrice = dupstr("thrice");

  kv.idx = 0;
  kv.data = once;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 1;
  kv.data = twice;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 2;
  kv.data = thrice;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 0;
  ret = ct_tree_unset(tree, &kv);

  kv.idx = 1;
  ret = ct_tree_unset(tree, &kv);

  kv.idx = 2;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);

  if(ret == CT_FOUND 
    && tree->len == 1 
    && !strcmp(kv.data, thrice) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_idx_set3_reset1(SuiteSet *set, void *data){
  int result;
  int ret;
  char *msg = dupstr("set and unset three result");
  struct ct_tree *tree = ct_tree_init(ct_cmp_idx, ct_is_void_idx, NULL);
  struct ct_leaf kv = {};

  char *one = dupstr("one");
  char *once = dupstr("once");
  char *two = dupstr("two");
  char *twoA = dupstr("twoA");
  char *twice = dupstr("twice");
  char *three = dupstr("three");
  char *thrice = dupstr("thrice");

  kv.idx = 0;
  kv.data = once;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 1;
  kv.data = twice;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 2;
  kv.data = thrice;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 1;
  kv.data = twoA;
  ret = ct_tree_set(tree, &kv);

  kv.idx = 1;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);

  if(ret == CT_FOUND 
    && tree->len == 3
    && !strcmp(kv.data, twoA) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}


static SuiteSet *get_idx_get_set(){
  return set_init("idx", 3, test_idx_set3_get3, test_idx_set3_unset2, test_idx_set3_reset1);

}
