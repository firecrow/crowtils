#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../tested/tested.c"
#include "poly.c"

int cnt = 0;
void free_mock(void *x){
    cnt++; 
}

int main(){
    CtlAbs *a = malloc(sizeof(CtlAbs));
    bzero(a, sizeof(CtlAbs));
    a->base.free = free_mock;
    a->base.class = 0;
    ctl_ref_incr(a);
    handle_case(a->base._refi == 0, "incr is noop for class unkonwn", a->base._refi, "");
    a->base.class = 1;
    ctl_ref_incr(a);
    handle_case(a->base._refi == 1, "incr sucessfully", a->base._refi, "");
    ctl_ref_incr(a);
    handle_case(a->base._refi == 2, "incr sucessfully", a->base._refi, "");
    ctl_ref_decr(a);
    handle_case(a->base._collected == NOT_COLLECTED, "first decr does not collect", a->base._collected, "");
    ctl_ref_decr(a);
    handle_case(a->base._collected == COLLECTED, "second decr does collect", a->base._collected, "");
    handle_case(cnt == 1, "second decr does collect free count incremented", cnt, "");
}
