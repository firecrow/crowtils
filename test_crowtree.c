#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "../tested/tested.c"
#include "../crowx/crowx.c"
#include "../poly/poly.c"
#include "../counted/counted.c"
#include "../crownumber/crownumber.c"
#include "treeprint.c"
#include "tree.c"

void *get_left(void *_n){
    struct node *n = (struct node *)_n;
    return n->children[0];
}

void *get_right(void *_n){
    struct node *n = (struct node *)_n;
    return n->children[1];
}

void *get_parent(void *_n){
    struct node *n = (struct node *)_n;
    return n->parent;
}

void out(void *_n){
    struct node *n = (struct node *)_n;
    CtlCounted *key = (CtlCounted *)n->key;
    if(n->is_red) printf("\x1b[31m%s\x1b[0m", ctl_counted_to_cstr(key));
    else printf("%s", ctl_counted_to_cstr(key));
}

void out_int(void *_n){
    struct node *n = (struct node *)_n;
    CtlInt *key = (CtlInt *)n->key;
    if(n->is_red) printf("\x1b[31m%d\x1b[0m", key->value);
    else printf("%d", key->value);
}

int main(){
    CtlTree *c = ctl_tree_alloc(ctl_tree_crownumber_int_cmp); 
    struct treeprint_head *tph;
    ctl_xptr(tph = malloc(sizeof(struct treeprint_head)));
    tph->get_left = get_left;
    tph->get_right = get_right;
    tph->get_parent = get_parent;
    tph->out = out_int;
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(7), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("seven\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(12), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("twelve\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(13), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("thirteen\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(1), 
        (CtlAbs *)ctl_counted_from_cstr("one"));
        printf("one\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(14), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("fourteen\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(15), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("fifteen\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(16), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("sixteen\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(2), 
        (CtlAbs *)ctl_counted_from_cstr("two"));
        printf("two\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(3), 
        (CtlAbs *)ctl_counted_from_cstr("three"));
        printf("three\n");
    /*ct_tree_print(tph, c->root);*/
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(8), 
        (CtlAbs *)ctl_counted_from_cstr("eight"));
        printf("eight\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(11), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("eleven\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(9), 
        (CtlAbs *)ctl_counted_from_cstr("nine"));
        printf("nine\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(4), 
        (CtlAbs *)ctl_counted_from_cstr("four"));
        printf("four\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(5), 
        (CtlAbs *)ctl_counted_from_cstr("five"));
        printf("five\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(20), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("twenty\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(21), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("twenty one\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(10), 
        (CtlAbs *)ctl_counted_from_cstr("ten"));
        printf("ten\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(6), 
        (CtlAbs *)ctl_counted_from_cstr("six"));
        printf("six\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(17), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("seventeen\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(18), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("eighteen\n");
    ct_tree_print(tph, c->root);
    ctl_tree_insert(c,
        (CtlAbs *)ctl_int_alloc(19), 
        (CtlAbs *)ctl_counted_from_cstr("seven"));
        printf("nineteen\n");


    ct_tree_print(tph, c->root);
    printf("size:%d\n", ctl_tree_size(c)); 
    CtlTreeNode *min = ctl_tree_min(c);
    printf("min:%d\n", ctl_key_int(min)); 
    CtlTreeNode *max = ctl_tree_max(c);
    printf("max:%d\n",  ctl_key_int(max)); 

    ctl_tree_next_node(c, c->root->children[GREATER]->children[GREATER]->children[GREATER]->children[LESS]);
    ctl_tree_next_node(c, c->root->children[GREATER]->children[GREATER]->children[GREATER]);
    ctl_tree_next_node(c, c->root->children[GREATER]->children[GREATER]);
    ctl_tree_next_node(c, c->root->children[GREATER]);
    ctl_tree_next_node(c, c->root->children[GREATER]->children[LESS]->children[LESS]);
    ctl_tree_next_node(c, c->root->children[LESS]->children[GREATER]->children[GREATER]);
    ctl_tree_next_node(c, c->root->children[LESS]->children[GREATER]->children[LESS]);
    ctl_tree_next_node(c, c->root->children[GREATER]->children[GREATER]->children[GREATER]->children[GREATER]);
    ctl_tree_next_node(c, c->root->children[LESS]->children[GREATER]->children[GREATER]->children[GREATER]);

    CtlTreeIter *iter = ctl_tree_iter(c);
    printf("\x1b[33msize:%d\x1b[0m\n", iter->size(iter));
    CtlTreeNode *node = NULL;
    while((node = iter->next(iter)) != NULL){
        printf("\x1b[33m(%d)\x1b[0m\n", ctl_key_int(node));
    }

    CtlTree *d = ctl_tree_alloc(ctl_tree_counted_cmp); 
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("evil"), 
        (CtlAbs *)ctl_counted_from_cstr("ever evangalizing eagotist"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("kilo"), 
        (CtlAbs *)ctl_counted_from_cstr("kk"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("carrot"), 
        (CtlAbs *)ctl_counted_from_cstr("calm or crazy came the cellist"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("dandilion"), 
        (CtlAbs *)ctl_counted_from_cstr("densly decadent delicatesen"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("mike"), 
        (CtlAbs *)ctl_counted_from_cstr("mmm"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("november"), 
        (CtlAbs *)ctl_counted_from_cstr("nnn"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("oscar"), 
        (CtlAbs *)ctl_counted_from_cstr("ooo"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("juliet"), 
        (CtlAbs *)ctl_counted_from_cstr("jjj"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("franklin"), 
        (CtlAbs *)ctl_counted_from_cstr("fast feverishly ferocious"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("hotel"), 
        (CtlAbs *)ctl_counted_from_cstr("happy hatred humanitarian holdover"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("india"), 
        (CtlAbs *)ctl_counted_from_cstr("in the inning of the inner ince"));
    ctl_tree_insert(d, 
        (CtlAbs *)ctl_counted_from_cstr("lima"), 
        (CtlAbs *)ctl_counted_from_cstr("lll"));

    /*
    printf("\n\n");
    tph->out = out;
    ct_tree_print(tph, d->root); 

    CtlCounted *v;
    v = (CtlCounted *)ctl_tree_get(d, (CtlAbs *)ctl_counted_from_cstr("carrot"));
    printf("carrot:%s\n", ctl_counted_to_cstr(v));

    v = (CtlCounted *)ctl_tree_get(d, (CtlAbs *)ctl_counted_from_cstr("franklin"));
    printf("carrot:%s\n", ctl_counted_to_cstr(v));
    */

    /* iter */
}
