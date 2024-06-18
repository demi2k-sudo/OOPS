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
        int x;
};

int main(){
    derived d;
    return 0;
}