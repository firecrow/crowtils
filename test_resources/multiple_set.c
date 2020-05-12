int test_set3_get3(SuiteSet *set, void *data){
  int result;
  int ret;
  char *results[3];
  char *msg = dupstr("set and get three result");
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

  kv.key = one;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);
  results[0] = kv.data;

  kv.key = two;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);
  results[1] = kv.data;

  kv.key = three;
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

int test_set3_unset2(SuiteSet *set, void *data){
  int result;
  int ret;
  char *msg = dupstr("set and unset three result");
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

  kv.key = one;
  ret = ct_tree_unset(tree, &kv);

  kv.key = two;
  ret = ct_tree_unset(tree, &kv);

  kv.key = three;
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

int test_set3_unset3_set1(SuiteSet *set, void *data){
  int result;
  int ret;
  char *msg = dupstr("set and unset three then set one new one");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *one = dupstr("one");
  char *once = dupstr("once");
  char *two = dupstr("two");
  char *twice = dupstr("twice");
  char *three = dupstr("three");
  char *thrice = dupstr("thrice");
  char *four = dupstr("four");
  char *fourth = dupstr("fourth");

  kv.key = one;
  kv.data = once;
  ret = ct_tree_set(tree, &kv);

  kv.key = two;
  kv.data = twice;
  ret = ct_tree_set(tree, &kv);

  kv.key = three;
  kv.data = thrice;
  ret = ct_tree_set(tree, &kv);

  kv.key = one;
  ret = ct_tree_unset(tree, &kv);

  kv.key = two;
  ret = ct_tree_unset(tree, &kv);

  kv.key = three;
  ret = ct_tree_unset(tree, &kv);

  kv.key = four;
  kv.data = fourth;
  ret = ct_tree_set(tree, &kv);

  kv.key = four;
  kv.data = NULL;
  ret = ct_tree_get(tree, &kv);

  if(ret == CT_FOUND 
    && tree->len == 1 
    && !strcmp(kv.data, fourth) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

static SuiteSet *get_multiple_set(){
  return set_init("multiple", 3, test_set3_get3, test_set3_unset2, test_set3_unset3_set1);
}
