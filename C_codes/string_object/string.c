#include<stdio.h>
#include<stdlib.h>

struct STRING {
    char *data;
    int length;
    int alloc;
    void (*append)(const struct STRING* self, char a);
    void (*display)(const struct STRING* self);
    void (*concat)(const struct STRING* self, char* a);
};


void append(struct STRING* self, char c){
    if(self->alloc > self->length+1)
    {
        self->data[self->length]=c;
        self->length++;
        self->data[self->length]='\0';
    }
    else{
        self->alloc = self->alloc*2;
        self->data = realloc(self->data,self->alloc);
        self->data[self->length]=c;
        self->length++;
        self->data[self->length]='\0';
    }
}

void display(struct STRING* self){
    printf("%s\n",self->data);
}

void concat(struct STRING* self, char* s){
    int count = 0,i=0;
    while(s[count]) count++;
    for(i=0;i<count;i++){
        self->append(self,s[i]);
    }
}


struct STRING* new_STRING(){
    struct STRING* s = malloc(sizeof(struct STRING));
    s->data = malloc(10);
    s->data[0] = '\0';
    s->alloc = 2;
    s->length = 0;
    s->append = &append;
    s->display = &display;
    s->concat = &concat;
    return s;
}

int main(){
    struct STRING* s = new_STRING();
    s->append(s,'h');
    s->append(s,'e');
    s->append(s,'l');
    s->append(s,'l');
    s->append(s,'o');
    s->display(s);
    s->concat(s," world");
    s->display(s);
}