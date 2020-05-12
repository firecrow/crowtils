/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */
#define KEYMAX 255
#define LESS 0
#define GREATER 1

enum status {
    OK = 0,
    NOT_FOUND = 1
};

typedef int (*ctl_tree_cmp)(CtlAbs *c, CtlAbs *b);

typedef struct node {
    CtlAbs *key; 
    CtlAbs *data; 
    int is_red;
    struct node *children[2];
    struct node *parent;
} CtlTreeNode;

typedef struct tree {
    CtlTreeNode *root;
    int size;
    int statno;
    ctl_tree_cmp cmp;
} CtlTree;

typedef struct tree_iter {
    CtlTree *tree;
    CtlTreeNode *current;
    CtlTreeNode *(*next)(struct tree_iter *iter);
    int (*size)(struct tree_iter *iter);
} CtlTreeIter;

CtlTreeNode *node_alloc(CtlAbs *key, CtlAbs *data){
    CtlTreeNode *n;  
    ctl_xptr(n = malloc(sizeof(CtlTreeNode)));
    bzero(n, sizeof(CtlTreeNode));
    n->key = key;
    n->data = data;
    n->children[GREATER] = n->children[LESS] = NULL;
    n->is_red = 0;
    n->parent = NULL;
    return n;
}

int ctl_tree_counted_cmp(CtlAbs *_a, CtlAbs *_b){
    CtlCounted *a = (CtlCounted *)_a;
    CtlCounted *b = (CtlCounted *)_b;
    int diff = strncmp(b->data, a->data, a->length);
    if(diff == 0) return b->length - a->length;
    return diff;
}

int ctl_tree_crownumber_int_cmp(CtlAbs *_a, CtlAbs *_b){
    CtlInt *a = (CtlInt *)_a;
    CtlInt *b = (CtlInt *)_b;
    return b->value - a->value;
}

int ctl_key_int(CtlTreeNode *node){
    if(!(node->key->base.class == CLASS_INT)){
        ctl_xerrlog("ctl_key_int called on a class other than CLASS_INT");
    }
    return ((CtlInt *)node->key)->value;
}

CtlTree *ctl_tree_alloc(ctl_tree_cmp cmp){
    CtlTree *t;
    ctl_xptr(t = malloc(sizeof(CtlTree)));
    bzero(t, sizeof(CtlTree));
    t->statno = OK;
    t->cmp = cmp;
    return t;
}

void rotate(CtlTree *t, CtlTreeNode *n){
    int ineq = n == n->children[GREATER] ? GREATER : LESS;
    CtlTreeNode *p = n->parent;
    CtlTreeNode *gp = p->parent;
    int p_ineq = p == gp->children[GREATER] ? GREATER : LESS;
    int n_ineq = n == p->children[GREATER] ? GREATER : LESS;

    p->children[n_ineq] = NULL;
    gp->children[p_ineq] = n;
    n->parent = gp;
   
    CtlTreeNode *o = n->children[!n_ineq];
    if(o){
        p->children[n_ineq] = o;
        o->parent = p;
        o->is_red = 1;
    }
    n->children[!n_ineq] = p;
    p->parent = n;

    p->is_red = 0;
    gp->is_red = 1;
    n->is_red = 0;
}

void swap(CtlTree *t, CtlTreeNode *n){
    CtlTreeNode *p = n->parent;
    CtlTreeNode *gp = p->parent;
    int p_ineq = p == gp->children[GREATER] ? GREATER : LESS;
    int n_ineq = n == p->children[GREATER] ? GREATER : LESS;
    CtlTreeNode *o = p->children[!n_ineq];

    gp->children[p_ineq] = n;
    n->parent = gp;

    n->children[!n_ineq] = p;
    p->parent = n;

    if(o){
        p->children[n_ineq] = o;
        o->parent = p;
    }else{
        p->children[n_ineq] = NULL;
    }
}

void balance(CtlTree *t, CtlTreeNode *n){
    if(!n->parent || !n->parent->parent)
        return;

    CtlTreeNode *p = n->parent;
    CtlTreeNode *gp = p->parent;
    int p_ineq = p == gp->children[GREATER] ? GREATER : LESS;
    int n_ineq = n == n->parent->children[GREATER] ? GREATER : LESS;
    CtlTreeNode *u = gp->children[!p_ineq]; 

    if(n->is_red && n->parent->is_red){
        if(u && u->is_red == 1){
            u->is_red = 0;
            p->is_red = 0;
            gp->is_red = 1;
            balance(t, gp);
        }else{
            if(p_ineq == n_ineq){
                rotate(t, n);
            }else{
                swap(t, n);
                rotate(t, p);
            }
        }
    }
}

void ctl_tree_insert(CtlTree *t, CtlAbs *key, CtlAbs *data){
    CtlTreeNode *n = node_alloc(key, data);
    int ineq;
    CtlTreeNode *next;
    CtlTreeNode *prev = NULL;
    if(t->root == NULL){
        n->is_red = 0;
        t->root = n; 
        t->statno = OK;
        return;
    }
    next = t->root;
    while(next != NULL){
        prev = next;
        ineq = t->cmp(n->key, next->key) < 0 ? GREATER : LESS;
        next = prev->children[ineq];
    }
    n->is_red = 1;
    n->parent = prev;
    prev->children[ineq] = n;
    balance(t, n);
}

CtlAbs *ctl_tree_get(CtlTree *t, CtlAbs *key){
    int ineq;
    CtlTreeNode *node = t->root;
    CtlTreeNode *next;
    CtlTreeNode *prev = NULL;
    if(node->parent){
        if(node->parent->parent) next = node->parent->parent;
        else next = node->parent;
    }else{
        next = node;
    }
    while(next != NULL){
        prev = next;
        int res = t->cmp(next->key, key);
        if(res == 0) 
            return next->data;
        ineq = res > 0 ? LESS : GREATER;
        next = prev->children[ineq];
    }
    return NULL;
}

static int get_ineq(CtlTreeNode *a){
    if(!a->parent) return 0;
    return a == a->parent->children[GREATER] ? GREATER: LESS;
}


CtlTreeNode *ctl_tree_next_node(CtlTree *tree, CtlTreeNode *orig){
    int ineq, nineq, i, diff, diff_child_less, diff_child_more,  diff_parent, l,g,p;
    ineq = get_ineq(orig);
    CtlTreeNode *prev = orig;
    CtlTreeNode *next = orig;
    CtlTreeNode *current = orig;
    int global = -1;
    int taken = 0;
    while(next){
        current = next;
        if(next->children[GREATER]){
            diff_child_more = tree->cmp(orig->key, next->children[GREATER]->key);
            g = ((CtlInt *)next->children[GREATER]->key)->value;
        }else{
            diff_child_more = -1;
            g = -1;
        }
        if(next->children[LESS]){
            diff_child_less = tree->cmp(orig->key, next->children[LESS]->key);
            l = ((CtlInt *)next->children[LESS]->key)->value;
        }else{
            diff_child_less = -1;
            l = -1;
        }
        if(next->parent){
            diff_parent = tree->cmp(orig->key, next->parent->key);
            p = ((CtlInt *)next->parent->key)->value;
        }else{
            diff_parent = -1;
            p = -1;
        }

        /*printf("\x1b[32m  more(%d):%d, less($%d):%d parent(%d):%d\x1b[0m\n", g, diff_child_more, l, diff_child_more, p, diff_parent);*/
        int min = 0;
        if(global != -1){
            min = global;
        }
        taken = 0;
        if(0 < diff_child_more && (global == -1 || diff_child_more < min) ){
            min = diff_child_more;
            prev = next->children[GREATER];
            taken = 1;
        }
        if(0 < diff_child_less && (diff_child_less < min || min <= 0)){
            min = diff_child_less;
            prev = next->children[LESS];
            taken = 1;
        }
        if(0 < diff_parent && (diff_parent < min || min <= 0)){
            min = diff_parent;
            prev = next->parent;
            taken = 1;
        }
        if(!taken){
            prev = NULL;
        }
        global = min;
        next = prev;
        if(!next){
            if(current == orig){ 
                prev = current;
               while(get_ineq(prev) == GREATER){
                    prev = prev->parent;
                    /*printf("\x1b[36mprev:(%d)\x1b[0m\n", ((CtlInt *)prev->key)->value);*/
               }
               if(get_ineq(prev) == LESS && prev->parent){
                   current = prev->parent;
               }
               break;
            }
        }else{
            /* printf("\x1b[33mnext:(%d)\x1b[0m\n", ((CtlInt *)next->key)->value);*/
        }

    }
    /*printf("\x1b[31m                       (%d)->%d\x1b[0m\n", ((CtlInt *)orig->key)->value, ((CtlInt *)current->key)->value);*/
    return current;
}

static CtlInt *gather_count(CtlTreeNode *n, CtlInt *count){
    int v = ((CtlInt *)n->key)->value;
    static int i = 0;

    if(count == NULL) count = ctl_int_alloc(0);
    count->value++;
    if(n->children[GREATER] != NULL){
        gather_count(n->children[GREATER], count);
    }
    if(n->children[LESS]!= NULL){
        gather_count(n->children[LESS], count);
    }
    return count;
}

int ctl_tree_size(CtlTree *t){
    return gather_count(t->root, NULL)->value;
}

static CtlTreeNode *ctl_tree_extreme(CtlTree *t, int ineq){
    CtlTreeNode *current = t->root;
    CtlTreeNode *next = current->children[ineq];
    while(next){
        current = next;
        next = current->children[ineq];
    }
    return current;
}

CtlTreeNode *ctl_tree_max(CtlTree *t){
    return ctl_tree_extreme(t, GREATER);
}

CtlTreeNode *ctl_tree_min(CtlTree *t){
    return ctl_tree_extreme(t, LESS);
}

static int ctl_tree_iter_size(CtlTreeIter *iter){
    return ctl_tree_size(iter->tree);
}

static CtlTreeNode *ctl_tree_iter_next(CtlTreeIter *iter){
    /*printf("next\n");*/
    CtlTreeNode *prev = iter->current;
    if(iter->current == NULL){
        /*printf("next null\n");*/
        iter->current = ctl_tree_min(iter->tree);
    }else{
        /*printf("next not null\n");*/
        iter->current = ctl_tree_next_node(iter->tree, iter->current);
    }
    if(iter->current == prev){
        /*printf("equal abort\n");*/
        return NULL;
    }
    return iter->current;
}

CtlTreeIter *ctl_tree_iter(CtlTree *tree){
    CtlTreeIter *iter;
    ctl_xptr(iter = malloc(sizeof(CtlTreeIter)));
    bzero(iter, sizeof(CtlTreeIter));
    iter->tree = tree;
    iter->next = ctl_tree_iter_next; 
    iter->size = ctl_tree_iter_size; 
    return iter;
}

/*
remove
iter
*/

