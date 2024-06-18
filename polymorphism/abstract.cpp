#include<iostream>
using namespace std;

class base{
    public:
    virtual void display() = 0;
};

class derv1:public base{
    public:
    void display(){
        cout<<"display of derv1"<<endl;
    }
};

class derv2:public base{
    public:
    void display(){
        cout<<"display of derv2"<<endl;
    }
};

int main(){
    derv1 dv1;
    derv2 dv2;

    base *ptr;

    ptr=&dv1;
    ptr->display();

    ptr=&dv2;
    ptr->display();

    return 0;
}

