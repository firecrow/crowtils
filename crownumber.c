/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */

/* 
 * intended for use cases where object oriented structure is necessary
 * for performance intensive applications, a static array of numbers
 * will be more effective, that being said this code definitely has it's 
 * place
 */
  
/* ---- int ----*/
typedef struct crowint {
    struct base base;
    int value;
}CtlInt;

static void int_free(void *ci){
    free(ci);
}

CtlInt *ctl_int_alloc(int x){
    CtlInt *ci;
    ctl_xptr(ci = malloc(sizeof(CtlInt)));
    bzero(ci, sizeof(CtlInt));
    ci->value = x;
    ci->base.free = int_free;
    ci->base.class = CLASS_INT;
    return ci;
}

CtlInt *ctl_int_incr(CtlInt *ci){
    return (CtlInt *)ctl_ref_incr((CtlAbs *)ci);
}

CtlInt *ctl_int_decr(CtlInt *ci){
    return (CtlInt *)ctl_ref_decr((CtlAbs *)ci);
}

/* ---- float ----*/
typedef struct crowfloat {
    struct base base;
    float value;
}CtlFloat;

static void float_free(void *cf){
    free(cf);
}

CtlFloat *ctl_float_alloc(float x){
    CtlFloat *cf;
    ctl_xptr(cf = malloc(sizeof(CtlFloat)));
    bzero(cf, sizeof(CtlFloat));
    cf->value = x;
    cf->base.free = float_free;
    return cf;
}

CtlInt *asCtlInt(CtlAbs *abs){
    if(abs->base.class != CLASS_INT){
        ctl_xerrlog("Attempted cast to CLASS_INT from incompatible class type");
    }
    return (CtlInt *)abs;
}

CtlFloat *ctl_float_incr(CtlFloat *cf){
    return (CtlFloat *)ctl_ref_incr((CtlAbs *)cf);
}

CtlFloat *ctl_float_decr(CtlFloat *cf){
    return (CtlFloat *)ctl_ref_decr((CtlAbs *)cf);
}
