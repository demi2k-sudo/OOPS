#include<conio.h>
#include<iostream>
#include<string>
using namespace std;

//check balance
//cash withdraw
//user details
//update mobile number

class ATM
{
    private:
        long int account_No;
        string name;
        int PIN;
        double balance;
        string mobile_no;

    public:
        void setData(long int account_No_a, string name_a, int PIN_a, double balance_a, string mobile_no_a)
        {
            account_No = account_No_a;
            name = name_a;
            PIN = PIN_a;
            balance = balance_a;
            mobile_no = mobile_no_a;
        }

        long int getAccountNo(){
            return account_No;
        }

        string getname(){
            return name;
        }

        int getPIN(){
            return PIN;
        }

        double getBalance(){
            return balance;
        }

        string getMobileNo(){
            return mobile_no;
        }

        void setMobile(string oldNumber, string newNumber){
            if(oldNumber == mobile_no){
                mobile_no = newNumber;
                cout<<endl<<"Successfully Updated Mobile Number!";
                _getch();
            }
            else{
                cout<<endl<<"Incorrect Old Number";
                _getch();
            }
        }

        void cashWithdraw(double amount){
            if(amount>balance){
                cout<<"Insufficient funds !"<<endl;
                _getch();
            }
            else{
                cout<<"Please collect your cash of Rs "<<amount<<endl;
                balance-=amount;
                cout<<"Current balance : "<<balance;
                _getch();
            }
        }        
        
};

int main(){
    long int enterAccountNo;
    int choice = 0, enterPIN;
    double cash;
    ATM user1;
    string oldM, newM;
    user1.setData(123132, "Demetrius", 1234, 40000, "98942023929");
    system("cls");
    bool cont = true;
    while(cont){
        system("cls");
        cout<<"**Welcome to Canara Bank**"<<endl;
        cout<<"\nEnter your account number :";
        cin>>enterAccountNo;
        cout<<"Enter your secret number : ";
        cin>>enterPIN;
        if(enterAccountNo==user1.getAccountNo() and enterPIN==user1.getPIN()){
            while(cont){
                system("cls");
                cout<<"**Welcome to Canara Bank**"<<endl;
                cout<<"1.Check Balance\n2.Withdraw Cash\n3.Show User Details\n4.Update Mobile Number\n5.Exit\nChoice : ";
                cin>>choice;
                switch(choice){
                    case 1:
                        cout<< "Available balance : "<<user1.getBalance()<<endl;
                        _getch();
                        break;
                    case 2:
                        
                        cout<<"Enter the amount to be withdrawed : ";
                        cin>>cash;
                        user1.cashWithdraw(cash);
                        
                        break;
                    case 3:
                        cout<<"Account No : "<<user1.getAccountNo()<<endl;
                        cout<<"Name : "<<user1.getname()<<endl;
                        cout<<"Balance : "<<user1.getBalance()<<endl;
                        cout<<"Mobile No : "<<user1.getMobileNo()<<endl;
                        _getch();
                        break;
                    case 4:
                        cout<<"Enter your old number : ";
                        cin>>oldM;
                        cout<<"Enter your new number : ";
                        cin>>newM;
                        user1.setMobile(oldM,newM);
                        break;
                    case 5:
                        cont=false;
                        break;
                    default:
                        cout<<"Invalid Choice!\n";
                        _getch();
                        break;
                }
            }
        }
        else{
            cout<<"Invalid Credentials !"<<endl;
            _getch();
        }
    }
}