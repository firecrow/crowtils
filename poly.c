/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */

enum classes {
    CLASS_INVALID = -1,
    CLASS_UNKNOWN = 0,
    CLASS_COUNTED,
    CLASS_PTRARRAY,
    CLASS_CAR,
    CLASS_TRAIN,
    CLASS_INT
};

enum collection_status {
    NOT_COLLECTED = 0,
    COLLECTED
};

struct base {
    enum classes class;
    int _refi;
    enum collection_status _collected;
    void (*free)(void *obj);
};

typedef struct abs {
    struct base base;
} CtlAbs;

CtlAbs *ctl_ref_incr(CtlAbs *obj){
    if(obj->base.class != CLASS_UNKNOWN){
        obj->base._refi++;
    }
    return obj;
}

CtlAbs *ctl_ref_decr(CtlAbs *obj){
    if(obj->base.class != CLASS_UNKNOWN){
        if(--obj->base._refi <= 0 && !obj->base._collected){
            obj->base._collected = 1;
            obj->base.free(obj);
        }
    }
    return obj;
}
