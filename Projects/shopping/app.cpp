#include<iostream>
#include<conio.h>
using namespace std;

class Item{
    int id;
    string name;
    int cost;
    int count;

    public:
    Item(){};
    Item(int i, string n, int c, int count):id(i),name(n),cost(c),count(count){}

    void create(int i, string n, int c, int count_n){
        id =  i;
        name =  n;
        cost =  c;
        count = count_n;
    }

    void display(){
        cout<<id<<"\t"<<name<<"\t"<<cost<<"\t"<<count<<"\t"<<count*cost<<endl;
    }

    int getCost(){
        return cost;
    }

    int getCount(){
        return count;
    }

    int getId(){return id;}
};

class Date{
    int day;
    int month;
    int year;
    public:
    Date(int d, int m, int y):day(d),month(m),year(y){}

    bool operator >=(Date &a){
        if(year==a.year){
            if(month==a.month){
                return day>=a.day;
            }
            else return month>=a.month;
        }
        else return year>=a.year;
    }

    bool operator <=(Date &a){
        if(year==a.year){
            if(month==a.month){
                return day<=a.day;
            }
            else return month<=a.month;
        }
        else return year<=a.year;
    }

    void display(){
        cout<<day<<"-"<<month<<"-"<<year;
    }
};

class Bill{
    int id;
    int cust_id;
    Item* list[10];
    int size=0;
    float total=0;
    Date date;

    public:
    
    Bill(int id, int cust_id, Date date):id(id),cust_id(cust_id),date(date) {}

    int getId(){return id;}

    Date getDate(){return date;}

    void printDetails(){
        cout<<"------------------------------------------\nID : "<<id<<endl;
        cout<<"Customer ID : "<<cust_id<<"\t\t";
        date.display();
        cout<<endl;
        for(int i=0;i<size;i++) list[i]->display();
        cout<<"Total:\t"<<total<<endl;
        cout<<"------------------------------------------"<<endl;
    }

    bool addItem( int prod_id, string n, int c, int count_n){
        Item * I = new Item(prod_id,n,c,count_n);
        // I->create(size,n,c,count_n);
        if(size==10) return false;
        list[size++] = I;
        total+=(I->getCost())*(I->getCount());
        return true;
    }

    bool isPresent(int prod_id){
        for(int i=0;i<size;i++){
            if(list[i]->getId()==prod_id) return true;
        }
        return false;
    }

    bool isCustomer(int cust){
        if (cust_id==cust) return true;
        return false;
    }

    Item* getItem(int prod_id){
        for(int i=0;i<size;i++){
            if(list[i]->getId()==prod_id) return list[i];
        }
        return NULL;
    }
};

class Application{
    Bill* archive[10];
    int size = 0;
    int items[3]={1,2,3};

    public:
    Application(){}

    bool addBill(Bill *b){
        if(size==10) return false;
        archive[size++] = b;
        return true;
    }

    void getBillById(int id){
        for(int i=0;i<size;i++){
            if(archive[i]->getId()==id){
                archive[i]->printDetails();
                return;
            }
        }
    }

    void getBillByDate(Date start, Date end){
        for(int i=0;i<size;i++){
            
            if(archive[i]->getDate()>=start and archive[i]->getDate()<=end){
                archive[i]->printDetails();
            }
        }
    }

    void getBillByItem(int prod_id){
        for(int i=0;i<size;i++){
            if(archive[i]->isPresent(prod_id)) archive[i]->printDetails();
        }
    }

    void getBillByCustomer(int cust_id){
        for(int i=0;i<size;i++){
            if(archive[i]->isCustomer(cust_id)) archive[i]->printDetails();
        }
    }

    void getRevenueByItem(int prod_id){
        float revenue=0;
        for(int i=0;i<size;i++){
            if(archive[i]->isPresent(prod_id)){
                Item* prod = archive[i]->getItem(prod_id);
                revenue += prod->getCost()*prod->getCount();
            }
        }
        cout<<prod_id<<" made a Revenue of "<<revenue<<endl;
    }
};

int main(){
    Bill b(1,3,Date(12,2,2003));
    b.addItem(1,"Product1",250,2);
    b.addItem(2,"Product2",20,4);
    b.addItem(3,"Product3",25,2);
    Bill a(4,5,Date(12,2,2015));
    a.addItem(1,"Product1",250,2);
    a.addItem(2,"Product2",20,4);
    Application app;
    app.addBill(&b);
    app.addBill(&a);
    // app.getBillById(4);
    // app.getBillByDate(Date(1,1,2010),Date(1,1,2040));
    // app.getBillByItem(3);
    // app.getRevenueByItem(3);
    // app.getBillByCustomer(5);
    bool flag = true;
    while(flag){
        system("cls");
        cout<<"Shopping Management System\n----------------------\n\nWelcome Admin!\n";
        cout<<"1.Get Bill by ID\n2.Get Bill by Date\n3.Get Bill by Item Id\n4.Get Revenue by Item\n5.Get Bill by Customer Id\n6.Exit\nChoice : ";
        int choice;
        cin>>choice;
        switch(choice){
            case 1:{
                cout<<"Enter Bill ID : ";
                int bill_id;
                cin>>bill_id;
                app.getBillById(bill_id);
                _getch();
                break;
            }
            case 2:{
                cout<<"Enter Start Date (dd mm yyyy) : ";
                int sd,sm,sy;
                cin>>sd>>sm>>sy;
                cout<<"Enter End Date (dd mm yyyy) : ";
                int ed,em,ey;
                cin>>ed>>em>>ey;
                app.getBillByDate(Date(sd,sm,sy),Date(ed,em,ey));
                _getch();
                break;
            }
            case 3:{
                cout<<"Enter the Item ID : ";
                int item_id;
                cin>>item_id;
                app.getBillByItem(item_id);
                _getch();
                break;
            }
            case 4:{
                cout<<"Enter the Item ID : ";
                int item_id;
                cin>>item_id;
                app.getRevenueByItem(item_id);
                _getch();
                break;
            }
            case 5:{
                cout<<"Enter Customer ID : ";
                int cust_id;
                cin>>cust_id;
                app.getBillByCustomer(cust_id);
                _getch();
                break;
            }
            case 6:{
                flag = false;
                break;
            }
        }
    }
}