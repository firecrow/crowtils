
int test_iter_apple_bananna(SuiteSet *set, void *data){
  /*
  $ ./treetil print -a apple bannana
  apple
  |
  <--bannana
  */

  int result;
  int ret;
  char *nexts[2];
  char *prevs[2];
  int idx = 0;
  char *msg = dupstr("iter apple bananna");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *apple = dupstr("apple");
  char *cider = dupstr("cider");
  char *bananna = dupstr("bananna");
  char *peal = dupstr("peal");

  kv.key = apple;
  kv.data = cider;
  ret = ct_tree_set(tree, &kv);

  kv.key = bananna;
  kv.data = peal;
  ret = ct_tree_set(tree, &kv);

  kv.key = NULL;
  while(!ct_tree_next(tree, &kv)){
    nexts[idx++] = kv.data;
  }

  idx = 0;
  kv.key = NULL;
  while(!ct_tree_previous(tree, &kv)){
    prevs[idx++] = kv.data;
  }

  if(
    !strcmp(nexts[0], cider) 
    && !strcmp(nexts[1], peal) 
    && !strcmp(prevs[0], peal) 
    && !strcmp(prevs[1], cider) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}


int test_iter_bananna_apple(SuiteSet *set, void *data){
  /*
  $ ./treetil print -a apple bananna
  bannana
  |
  >--apple
  */

  int result;
  int ret;
  char *nexts[2];
  char *prevs[2];
  int idx = 0;
  char *msg = dupstr("iter apple bananna");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *apple = dupstr("apple");
  char *cider = dupstr("cider");
  char *bananna = dupstr("bananna");
  char *peal = dupstr("peal");

  kv.key = bananna;
  kv.data = peal;
  ret = ct_tree_set(tree, &kv);

  kv.key = apple;
  kv.data = cider;
  ret = ct_tree_set(tree, &kv);


  kv.key = NULL;
  while(!ct_tree_next(tree, &kv)){
    nexts[idx++] = kv.data;
  }

  idx = 0;
  kv.key = NULL;
  while(!ct_tree_previous(tree, &kv)){
    prevs[idx++] = kv.data;
  }

  if(
    !strcmp(nexts[0], cider) 
    && !strcmp(nexts[1], peal) 
    && !strcmp(prevs[0], peal) 
    && !strcmp(prevs[1], cider) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}


int test_iter_apple_bananna_carrot(SuiteSet *set, void *data){
  /*
  $ ./treetil print -a apple bannana carrot
  apple
  |
  <--bannana
     |
     <--carrot
  */

  int result;
  int ret;
  char *nexts[3];
  char *prevs[3];
  int idx = 0;
  char *msg = dupstr("iter apple bananna");
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
  while(!ct_tree_next(tree, &kv)){
    nexts[idx++] = kv.data;
  }

  idx = 0;
  kv.key = NULL;
  while(!ct_tree_previous(tree, &kv)){
    prevs[idx++] = kv.data;
  }

  if(
    !strcmp(nexts[0], cider) 
    && !strcmp(nexts[1], peal) 
    && !strcmp(nexts[2], stick) 
    && !strcmp(prevs[0], stick) 
    && !strcmp(prevs[1], peal) 
    && !strcmp(prevs[2], cider) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}


int test_iter_bananna_apple_carrot(SuiteSet *set, void *data){
  /*
  $ ./treetil print -a bannana apple carrot
  bannana
  |
  >--apple
  |
  <--carrot
  */

  int result;
  int ret;
  char *nexts[3];
  char *prevs[3];
  int idx = 0;
  char *msg = dupstr("iter apple bananna");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *apple = dupstr("apple");
  char *cider = dupstr("cider");
  char *bananna = dupstr("bananna");
  char *peal = dupstr("peal");
  char *carrot = dupstr("carrot");
  char *stick = dupstr("stick");

  kv.key = bananna;
  kv.data = peal;
  ret = ct_tree_set(tree, &kv);

  kv.key = apple;
  kv.data = cider;
  ret = ct_tree_set(tree, &kv);

  kv.key = carrot;
  kv.data = stick;
  ret = ct_tree_set(tree, &kv);

  kv.key = NULL;
  while(!ct_tree_next(tree, &kv)){
    nexts[idx++] = kv.data;
  }

  idx = 0;
  kv.key = NULL;
  while(!ct_tree_previous(tree, &kv)){
    prevs[idx++] = kv.data;
  }

  if(
    !strcmp(nexts[0], cider) 
    && !strcmp(nexts[1], peal) 
    && !strcmp(nexts[2], stick) 
    && !strcmp(prevs[0], stick) 
    && !strcmp(prevs[1], peal) 
    && !strcmp(prevs[2], cider) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

int test_iter_apple_carrot_bananna(SuiteSet *set, void *data){
  /*
  $ ./treetil print -a apple carrot bannna
  apple
  |
  <--carrot
     |
     >--bannna
  */

  int result;
  int ret;
  char *nexts[3];
  char *prevs[3];
  int idx = 0;
  char *msg = dupstr("iter apple bananna");
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

  kv.key = carrot;
  kv.data = stick;
  ret = ct_tree_set(tree, &kv);

  kv.key = bananna;
  kv.data = peal;
  ret = ct_tree_set(tree, &kv);


  kv.key = NULL;
  while(!ct_tree_next(tree, &kv)){
    nexts[idx++] = kv.data;
  }

  idx = 0;
  kv.key = NULL;
  while(!ct_tree_previous(tree, &kv)){
    prevs[idx++] = kv.data;
  }

  if(
    !strcmp(nexts[0], cider) 
    && !strcmp(nexts[1], peal) 
    && !strcmp(nexts[2], stick) 
    && !strcmp(prevs[0], stick) 
    && !strcmp(prevs[1], peal) 
    && !strcmp(prevs[2], cider) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}


int test_iter_carrot_bananna_apple(SuiteSet *set, void *data){
  /*
  $ ./treetil print -a carrot banaana apple
  carrot
  |
  >--banaana
     |
     >--apple
  */

  int result;
  int ret;
  char *nexts[3];
  char *prevs[3];
  int idx = 0;
  char *msg = dupstr("iter apple bananna");
  struct ct_tree *tree = ct_tree_init(ct_cmp_alpha, ct_is_void_alpha, NULL);
  struct ct_leaf kv = {};

  char *apple = dupstr("apple");
  char *cider = dupstr("cider");
  char *bananna = dupstr("bananna");
  char *peal = dupstr("peal");
  char *carrot = dupstr("carrot");
  char *stick = dupstr("stick");

  kv.key = carrot;
  kv.data = stick;
  ret = ct_tree_set(tree, &kv);

  kv.key = bananna;
  kv.data = peal;
  ret = ct_tree_set(tree, &kv);

  kv.key = apple;
  kv.data = cider;
  ret = ct_tree_set(tree, &kv);

  kv.key = NULL;
  while(!ct_tree_next(tree, &kv)){
    nexts[idx++] = kv.data;
  }

  idx = 0;
  kv.key = NULL;
  while(!ct_tree_previous(tree, &kv)){
    prevs[idx++] = kv.data;
  }

  if(
    !strcmp(nexts[0], cider) 
    && !strcmp(nexts[1], peal) 
    && !strcmp(nexts[2], stick) 
    && !strcmp(prevs[0], stick) 
    && !strcmp(prevs[1], peal) 
    && !strcmp(prevs[2], cider) 
  ){
    result = 0;
  }else{
    result = 1;
  }
  next(set, result, msg, data);
}

SuiteSet *get_iter_next_prev_set(){
  return set_init("iter internals", 6, 
    test_iter_apple_bananna, 
    test_iter_bananna_apple, 
    test_iter_apple_bananna_carrot,
    test_iter_bananna_apple_carrot,
    test_iter_apple_carrot_bananna,
    test_iter_carrot_bananna_apple);
}
