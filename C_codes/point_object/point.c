#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Point{
    int x;
    int y;
    void (*dump)(const struct Point* self);
    void (*del)(const struct Point* self);
    double (*origin)(const struct Point* self);
};

void point_dump(struct Point* self){
    printf("x : %d y: %d\n",self->x,self->y);
}

void point_del(struct Point* self){
    free(self);
}

double point_origin(struct Point* self){
    return sqrt(self->x*self->x+self->y*self->y);
}

struct Point* new_point(int x, int y){
    struct Point* pt = malloc(sizeof(struct Point));
    pt->x = x;
    pt->y = y;
    pt->dump = &point_dump;
    pt->del = &point_del;
    pt->origin = &point_origin;
    return pt;
}

int main(){
    struct Point* pt = new_point(4,5);
    pt->dump(pt);
    printf("Origin : %f\n",pt->origin(pt));
    pt->del(pt);
}