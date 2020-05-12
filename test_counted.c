#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../crowx/crowx.c"
#include "../poly/poly.c"
#include "../tested/tested.c"
#include "counted.c"

int main(){
    char alpha[]="apples and aphabet anchored in alaska";
    char bravo[]="beauty is back in black";

    char *aclone = dup_mem(alpha, strlen(alpha));
    int clone_r = strcmp(alpha, aclone);
    handle_case(clone_r == 0, "dup_mem is accurate", clone_r, "");

    CtlCounted *c = ctl_counted_alloc(NULL, 0);
    handle_case(c->length == 0, "new counted length = 0", c->length, "");
    handle_case(c->alloc_length == COUNTED_INITIAL_SIZE, 
        "new counted alloc_length = COUNTED_INITIAL_SIZE", 
        c->alloc_length, 
        "");
    handle_case(c->base.class == CLASS_COUNTED, "new counted class is set", 
    c->base.class, "");

    c = ctl_counted_from_cstr(bravo);
    handle_case(c->length == strlen(bravo), "from cstr length", c->length, "");
    handle_case(c->alloc_length > COUNTED_INITIAL_SIZE, "from cstr accurate size", c->alloc_length, "");
    clone_r = strncmp(c->data, bravo, c->length);
    handle_case(clone_r == 0, "new counted content matches original cstr", clone_r, "");


    CtlCounted *b = clone(c);
    handle_case(c->length == b->length, "clone = length", c->length, "");
    handle_case(c->length == b->length, "clone = length", c->length, "");
    handle_case(c->alloc_length == b->alloc_length, "clone = alloc_length", c->alloc_length, "");
    clone_r = strncmp(c->data, b->data, c->length);
    handle_case(clone_r == 0, "clone counted = data", clone_r, "");

    char *s = ctl_counted_to_cstr(c);
    clone_r = strcmp(s, bravo);
    handle_case(clone_r == 0, "to cstr content eq", clone_r, "");
   
    CtlCounted *d = ctl_counted_format("%d:%s, %lu", 10, "hi there", sizeof(CtlCounted));
    clone_r = strncmp("10:hi there, 4", d->data, d->length);
    handle_case(clone_r == 0, "counted format content eq", clone_r, "");

    CtlCounted *e = ctl_counted_alloc(NULL, 0);
    char charlie[] = "cataloging";
    char delta[] = " dogs and dudes, and deliveries";
    char together[] = "cataloging dogs and dudes, and deliveries";
    ctl_counted_push(e, charlie, strlen(charlie)); 
    clone_r = strncmp(e->data, charlie , d->length);
    handle_case(clone_r == 0, "push has first set of conts", clone_r, "");
    handle_case(e->alloc_length == COUNTED_INITIAL_SIZE, "push alloc is initial", e->alloc_length, "");

    ctl_counted_push(e, delta, strlen(delta)); 
    clone_r = strncmp(e->data, together , d->length);
    handle_case(clone_r == 0, "push has first set of conts", clone_r, "");
    handle_case(e->alloc_length > COUNTED_INITIAL_SIZE, "push alloc has grown", e->alloc_length, "");
}

