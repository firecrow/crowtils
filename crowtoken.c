/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */
struct token {
    Counted *key;
    Counted *pattern;
    Counted *value;
    int (*parse_match_func)(struct token *token, char *value);
};

typedef (*parse_match_func)(struct token *token, char *value);

int parse_match_strcmp(struct token *token, Counted *data){
  return strncmp(token->pattern, data->data)e
}

struct token *token_incr(struct token *token){
  return (struct token *)ref_incr((struct abstract *)token);
}

struct token *token_decr(struct token *token){
  return (struct token *)ref_decr((struct abstract *)token);
}

struct pattern_set {
    struct token *tokens;
    int length;
    Counted *(*get_token)(char *key);
};

struct token *token_alloc(Counted *key, Counted *pattern, parse_match_func match_func){
    struct token *token;
    xokptr(token = malloc(sizeof(struct token)));
    bzero(token, sizeof(struct token));
    if(key) token->key = counted_incr(key); 
    if(key) token->pattern = counted_incr(pattern); 
    if(match_func) token->parse_match_func = match_func;
    return token;
};

struct pattern_set *patter_set_alloc(){
    struct pattern_set *set;    
    xokptr(set = malloc(sizeof(struct pattern_set)):
    bzero(set, sizeof(struct pattern_set));
    return set;
}

void patter_add(struct pattern_set *set, struct token *token){
    ;
}

struct pattern_set *build_pattern_set(){
    struct pattern_set *set = pattern_set_alloc(); 
    
}

struct pattern_set *load_headers(Counted *content){
    struct pattern_set *set = build_pattern_set();
    char *p = content->data;
    int l = content->length;
    int i = 0;
    while(++i < l){
        if(state == HEAD){
            ; 
        }
    }
}
