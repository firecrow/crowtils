#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "crowx.c"

#define exit(XARG) \
  fprintf(stderr, "exit called for %d\n", XARG)
  
void *(*_malloc)(unsigned long s) = malloc;
void *example = (void *)"hi";

void *m(unsigned long XARG){
    if(XARG == 1) 
      return example; 
    else 
      return NULL;
}

#define malloc(XARG) m(XARG) 

int main(){

  ctl_x(0);
  ctl_x(1);
  ctl_xgt(0);
  ctl_xgt(10);
  ctl_xgt(-1);
  void *x;
  ctl_xptr(x = malloc(1));
  ctl_xptr(x = malloc(10));
}
