/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */


enum ctl_status { 
    CTL_INVALID=-1,
    CTL_NULL=0,
    CTL_ERR=1,
    CTL_OK,
    CTL_NOT_STARTED,
    CTL_PENDING,
    CTL_ACTIVE,
    CTL_COMPLETE
};


enum classes {
    CLASS_INVALID = -1,
    CLASS_NULL = 0,
    CLASS_UNDEFINED,
    CLASS_COUNTED,
    CLASS_PTRARRAY,
    CLASS_CAR,
    CLASS_TREE,
    CLASS_TRAIN,
    CLASS_INT,
    CLASS_BLOCK,
    CLASS_CELL,
    CLASS_OPP,
    CLASS_SYMBOL,
    CLASS_CTX,
    CLASS_SEP,
    CLASS_STATEMENT,
    CLASS_STMT_LEAD
};

enum collection_status {
    NOT_COLLECTED = 0,
    COLLECTED
};

struct base {
    enum classes class;
    int id;
    int _refi;
    enum collection_status _collected;
    void (*free)(void *obj);
};

typedef struct abs {
    struct base base;
} CtlAbs;

CtlAbs *ctl_ref_incr(CtlAbs *obj){
    if(obj->base.class != CLASS_NULL){
        obj->base._refi++;
    }
    return obj;
}

CtlAbs *ctl_ref_decr(CtlAbs *obj){
    if(obj->base.class != CLASS_NULL){
        if(--obj->base._refi <= 0 && !obj->base._collected){
            obj->base._collected = 1;
            obj->base.free(obj);
        }
    }
    return obj;
}
