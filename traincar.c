/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */

#ifndef CAR_SIZE 
    #define CAR_SIZE 1024
#endif

enum train_content {
    CTL_CONTENT,
    CTL_NO_CONTENT
};

typedef void (*content_func)(int s, char *content, int length);

struct car {
    struct base base;
    char content[CAR_SIZE];
    int length;
    struct car *next;
};

typedef struct train {
    struct base base;
    struct car* start;
    int length;
} CtlTrain;


struct iter {
    int idx; 
    CtlTrain *train;
    struct car *car;
    char *value;
};

void car_free(void *obj){
    struct car *car = (struct car *)obj;
    free(car);
}

struct car *car_incr(struct car *car){
    return (struct car *)ctl_ref_incr((CtlAbs *)car);
}

struct car *car_decr(struct car *car){
    return (struct car *)ctl_ref_decr((CtlAbs *)car);
}

struct car *car_alloc(){
    struct car *car = (struct car *) malloc(sizeof(struct car));
    bzero(car, sizeof(struct car));
    car->base.class = CLASS_CAR;
    car->base.free = car_free;
    return car;
}

struct car *car_alloc_with(char *str, int length){
    struct car *car = car_alloc();
    if(length > CAR_SIZE-1){
        ctl_xerrlog("length larger than CAR_SIZE"); 
    }
    memcpy(car->content, str, length);
    car->length = length;
    return car;
}

struct car *car_alloc_with_string(char *str){
    return car_alloc_with(str, strlen(str));
}

void train_free(void *obj){
    CtlTrain *train = (CtlTrain *)obj;
    struct car *next = train->start;
    struct car *current = next;
    int i = 0;
    do {
        next = current->next;
        car_decr(current);
        current = next;
    }while(current);
}

CtlTrain *train_incr(CtlTrain *train){
    return (CtlTrain *)ctl_ref_incr((CtlAbs *)train);
}

CtlTrain *train_decr(CtlTrain *train){
    return (CtlTrain *)ctl_ref_decr((CtlAbs *)train);
}

CtlTrain *train_alloc(){
    CtlTrain *train =   (CtlTrain *) malloc(sizeof(CtlTrain));
    bzero(train, sizeof(CtlTrain));
    train->base.class = CLASS_TRAIN;
    train->base.free = train_free;
    train->length = 1;
    return train;
}

void train_init(CtlTrain *train){
    train->start = car_alloc();
}

struct car *get_last_car(CtlTrain *train){
    struct car *car = train->start;
    struct car *prev;
    do {
        prev = car;
    } while((car = car->next));
    if (prev) 
        return prev;
    else
        ctl_xerrlog("end car not found"); 
}

int add_car(CtlTrain *train, struct car *item){
    if(train->start == NULL){
        train->start = car_incr(item);
        return 0;
    }else{
        get_last_car(train)->next = car_incr(item);
        train->length++;
        return train->length;
    }
}

struct car *train_pickup(CtlTrain *train){
    train->length++;
    return get_last_car(train)->next = car_alloc();
}

struct iter *trian_iter(CtlTrain *train){
	struct iter *iter;
	ctl_xptr(iter = malloc(sizeof(struct iter)));
	bzero(iter, sizeof(struct iter));
	iter->train = train;
	iter->car = train->start;
	iter->idx = 0;
	iter->value = train->start->content;
    return iter;
}

int train_content_get(struct iter *iter){
	if(iter->value == NULL){
		iter->value = iter->car->content;
		return CTL_CONTENT;
	}
	if(iter->idx+1 < iter->car->length){
		iter->value++;
		iter->idx++;
		return CTL_CONTENT;
    }
    if(iter->car->next){
        iter->car = iter->car->next;
        iter->idx = 0;
        iter->value = NULL;
    }
    return CTL_NO_CONTENT;
}

void train_add_content(CtlTrain *train, char *buff, int length){
    struct car *car = get_last_car(train);
    do {
        int available = CAR_SIZE-car->length;
        if(length < available){
            memcpy(car->content+car->length, buff, length);
            car->length += length;
            break;
        }else{
            memcpy(car->content+car->length, buff, available);
            buff+=available;
            length -= available;
            car->length += available;
            car = train_pickup(train);
        }
    } while(length > 0);
}
