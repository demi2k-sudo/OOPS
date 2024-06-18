#include<iostream>
using namespace std;

class User{
    public:
        string name;
        int age;
        bool is_male;
        User(string name, int age, bool is_male){
            this->name = name;
            this->age = age;
            this->is_male = is_male;
            count++;
        }
        static int count;
        static void displayCount(){
            cout<<count<<endl;
        }
};

int User::count = 0;

int main (){
    User u1("A", 20, true);
    User u2("B", 21, false);
    User u3("C", 22, true);
    User u4("D", 23, false);
    User u5("E", 24, true);
    User::displayCount();
    cout<<u1.count<<endl;
    cout<<u5.count<<endl;
    cout<<User::count<<endl;
    return 0;
}

