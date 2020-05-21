/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct treeprint_head {
  void *(*get_left)(void *);
  void *(*get_right)(void *);
  void *(*get_parent)(void *);
  void (*out)(void *);
  int level;
  void *root;
  bool open[32];
};

void ct_tree_print_fnc(struct treeprint_head *tph, void *node, bool is_left){
  int show_level;
  int i;
  if(tph->get_parent(node) && node != tph->root){
    i = 1;
    while(i < tph->level){
      printf(tph->open[i] ? "|" : " ");
      printf("  ");
      i++;
    }
    printf("|\n");
  }
  i = 1;
  while(i < tph->level){
    printf(tph->open[i] ? "|" : " ");
    printf("  ");
    i++;
  }
  void *parent = tph->get_parent(node);
  if(parent && node != tph->root){
    printf(is_left ? "(+)" : "(-)");
    printf("-");
  }
  tph->out(node);
  printf("\n");
  void *next;
  if((next = tph->get_right(node))){
    tph->level++;
    if(tph->get_left(node)){
      tph->open[tph->level] = true;
    }
    ct_tree_print_fnc(tph, next, true);
    tph->level--;
  }
  if((next = tph->get_left(node))){
    tph->level++;
    tph->open[tph->level] = false;
    ct_tree_print_fnc(tph, next, false);
    tph->level--;
  }
}

void ct_tree_print(struct treeprint_head *tph, void *root){
  tph->level = 0;
  tph->root = root;
  ct_tree_print_fnc(tph, root, true);
}

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


