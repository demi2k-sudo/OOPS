#include<iostream>
using namespace std;

class base{
    public:
        base(){
            cout<<"Base class Default constructor"<<endl;
        }
        base(int x){
            cout<<"Base class parameterized constructor"<<endl;
        }
};

class derived : public base{
    public:
        derived():base(){
            cout<<"Derived class Default constructor"<<endl;
        }
        derived(int y):base(y){
            cout<<"Derived class parameterized constructor"<<endl;
        }
};

int main(){
    derived d(5);
    derived a;
    return 0;
}