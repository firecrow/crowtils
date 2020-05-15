/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */
#define COUNTED_INITIAL_SIZE 16

typedef struct counted {
    struct base base;
    char *data;
    size_t length; 
    size_t alloc_length;
} CtlCounted;

static void ctl_counted_free(void *obj){
    CtlCounted *c = (CtlCounted *)obj;
    free(c->data);
    free(c);
}

static char *dup_mem(const char *orig, size_t length){
    char *new;
    ctl_xptr(new = malloc(length));
    memcpy(new, orig, length);
    return new;
}

CtlCounted *ctl_counted_alloc(char *data, size_t length){
    CtlCounted *c;
    ctl_xptr(c = malloc(sizeof(CtlCounted)));
    bzero(c, sizeof(CtlCounted));
    c->base.class = CLASS_COUNTED;
    c->base.free = ctl_counted_free;
    if(data == NULL){
        size_t initial_size = COUNTED_INITIAL_SIZE;
        if(length) initial_size = length;
        ctl_xptr(c->data = malloc(initial_size));
        c->alloc_length = initial_size;
        bzero(c->data, c->alloc_length);
    }else{
        c->data = dup_mem(data, length);
        c->length = length;
        c->alloc_length = length;
    }
    return c;
}

struct counted *ctl_counted_from_cstr(char *str){
    return ctl_counted_alloc(str, strlen(str));
}

CtlCounted *clone(CtlCounted *c){
    return ctl_counted_alloc(c->data, c->length);
}

char *ctl_counted_to_cstr(CtlCounted *c){
    char *new;
    ctl_xptr(new = malloc(c->length+1));
    memcpy(new, c->data, c->length);
    new[c->length] = '\0';
    return new;
}

CtlCounted *ctl_counted_format(const char *restrict format, ...){
  va_list args;
  va_list args_copy;
  va_start(args, format);
  /* copying the args list because when we do the first vsnprinf it will be
   * consumed, the args_copy is for the second time */
  va_copy(args_copy, args);
  /* put it on an array too small on purpose to get the full length in the
   * returned value */
  char x[] = " ";
  int length = vsnprintf(x, 1, format, args)+1;
  CtlCounted *c = ctl_counted_alloc(NULL, length);
  vsnprintf(c->data, length, format, args_copy);
  c->length = length;
  va_end(args);
  va_end(args_copy);
  return c;
}

void ctl_counted_push(CtlCounted *c, char *data, size_t length){
    if(c->length+length > c->alloc_length){
        while((c->alloc_length *= 2) < c->length+length){}
        ctl_xptr(c->data = realloc(c->data, c->alloc_length));
    }
    memcpy(c->data+c->length, data, length);
    c->length += length;
}
