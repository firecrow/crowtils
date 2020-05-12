#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../crowx/crowx.c"
#include "../tested/tested.c"
#include "../poly/poly.c"
#include "../counted/counted.c"
#include "../crray/crray.c"
#define CAR_SIZE 32
#include "traincar.c"

void show_train(CtlTrain *train){
    printf("----- train %d ----->\n", train->length);
    struct car *car = train->start;
    int i = 0;
    do {
        write(1, ">\n", 2);
        write(1, car->content, car->length);
        write(1, "\n<\n", 3);
    } while((car = car->next));
}

int main(){
    write(1, "1\n", 2);
    CtlTrain *t = train_alloc();
    train_init(t);
    write(1, "2\n", 2);
    CtlCounted *a = ctl_counted_from_cstr("alabama in the autum with ale and acolades");
    train_add_content(t, a->data, a->length);
    CtlCounted *b = ctl_counted_from_cstr(" baskets of bunble bees bouncing before bed");
    train_add_content(t, b->data, b->length);
    CtlCounted *c = ctl_counted_from_cstr(" california in the crisp castles out of clay");
    train_add_content(t, c->data, c->length);
    printf("%zu %zu %zu: %zu\n", a->length, b->length, c->length, a->length + b->length + c->length);
    show_train(t);
    struct car *r = t->start;
    int diff = strncmp("alabama in the autum with ale an", r->content, r->length); 
    handle_case(diff == 0, "first car comparison", diff, "");
    r = r->next;
    diff = strncmp("d acolades baskets of bunble bee", r->content, r->length); 
    handle_case(diff == 0, "second car comparison", diff, "");
    r = r->next;
    diff = strncmp("s bouncing before bed california", r->content, r->length); 
    handle_case(diff == 0, "third car comparison", diff, "");
    r = r->next;
    diff = strncmp(" in the crisp castles out of cla", r->content, r->length); 
    handle_case(diff == 0, "fourth car comparison", diff, "");
    r = r->next;
    diff = strncmp("y", r->content, r->length); 
    handle_case(diff == 0, "fifth car comparison", diff, "");
}
