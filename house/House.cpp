#include<iostream>
#include<string>
using namespace std;

class house
{
    private:
    
    int length = 0;
    int breadth = 0;

    public:
    //member function
    void setData(int l, int b){
        length = l;
        breadth = b;
    }

    void area(){
        cout<<"Area of the house : "<<length*breadth;
    }
};

int main(){
    house h;
    h.setData(10,20);
    h.area();
    return 0;
}