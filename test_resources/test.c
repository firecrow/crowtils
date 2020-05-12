#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../crowtils/crowtils.c"
#include "suite.c"
#include "tree.c"
#include "test/basic_set.c"
#include "test/multiple_set.c"
#include "test/iterator_set.c"
#include "test/bug_set.c"
#include "test/iter_next_prev_set.c"
#include "test/idx_get_set.c"

int main(){
  start(get_basic_set(), NULL);
  start(get_multiple_set(), NULL);
  start(get_iterator_set(), NULL);
  start(get_bug_set(), NULL);
  start(get_iter_next_prev_set(), NULL);
  start(get_idx_get_set(), NULL);
}
