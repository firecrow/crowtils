int test_empty_iter(SuiteSet *set, void *data){
  int result;
  int ret;
  int idx;
  int res;
  char *msg = dupstr("try to iterate on empty object");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {NULL, 0, NULL};
  while(!(res = ct_tree_next(tree, &kv))){}
  if(res == CT_NOT_FOUND){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_set3_iter(SuiteSet *set, void *data){
  int result;
  int ret;
  char *results[3];
  int idx = 0;
  char *msg = dupstr("set three values and then iterate through them");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *apple = dupstr("apple");
  char *cider = dupstr("cider");
  char *bananna = dupstr("bananna");
  char *peal = dupstr("peal");
  char *carrot = dupstr("carrot");
  char *stick = dupstr("stick");

  kv.key = apple;
  kv.data = cider;
  ret = ct_tree_set(tree, &kv);

  kv.key = bananna;
  kv.data = peal;
  ret = ct_tree_set(tree, &kv);

  kv.key = carrot;
  kv.data = stick;
  ret = ct_tree_set(tree, &kv);

  bzero(&kv, sizeof(struct ct_leaf));
  while(!ct_tree_next(tree, &kv)){
    results[idx++] = kv.data;
  }

  if(
    !strcmp(results[0], cider) 
    && !strcmp(results[1], peal) 
    && !strcmp(results[2], stick) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_set3_iter_prev(SuiteSet *set, void *data){
  int result;
  int ret;
  char *results[3];
  int idx = 0;
  char *msg = dupstr("set three values and then iterate through them");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *apple = dupstr("apple");
  char *cider = dupstr("cider");
  char *bananna = dupstr("bananna");
  char *peal = dupstr("peal");
  char *carrot = dupstr("carrot");
  char *stick = dupstr("stick");

  kv.key = apple;
  kv.data = cider;
  ret = ct_tree_set(tree, &kv);

  kv.key = bananna;
  kv.data = peal;
  ret = ct_tree_set(tree, &kv);

  kv.key = carrot;
  kv.data = stick;
  ret = ct_tree_set(tree, &kv);

  kv.key = NULL;
  while(!ct_tree_previous(tree, &kv)){
    results[idx++] = kv.data;
  }

  if(
    !strcmp(results[0], stick) 
    && !strcmp(results[1], peal) 
    && !strcmp(results[2], cider) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

static SuiteSet *get_iterator_set(){
  return set_init("iterator", 3, test_empty_iter, test_set3_iter, test_set3_iter_prev);
}
