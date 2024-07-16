#include<iostream>
#include<conio.h>
using namespace std;

#define MAX_USERS 10
#define MAX_EMAILS 20
#define MAX_DM 10

class User{
    int u_id;
    string u_name;
    string u_address;
    string u_password;
    static int u_count;

    public:
    User(){}
    User(string u_name_a, string u_address_a, string u_password_a){
        u_id = ++u_count;
        u_name = u_name_a;
        u_address = u_address_a;
        u_password = u_password_a;
    }

    string getAddress(){return u_address;}

    string getPassword(){return u_password;}

    string getName(){return u_name;}
};

class Mail{
    int m_id;
    string f_address;
    string t_address;
    string content;
    
    public:
    Mail(){}
    static int m_count;

    Mail(string f_address_a,string t_address_a, string content_a){
        f_address = f_address_a;
        t_address = t_address_a;
        content = content_a;
        m_id = ++m_count;
    }

    string getFAddress(){
        return f_address;
    }

    string getTAddress(){
        return t_address;
    }

    string getContent(){
        return content;
    }
};

class Application{
    User* users[MAX_USERS];
    Mail* mails[MAX_EMAILS];
    int user_count = 0;
    int mail_count = 0;
    User* currentUser = NULL;

    public:
    Application(){}

    bool signUp(string u_name, string u_address, string u_password){
        User* u = new User(u_name,u_address,u_password);
        users[user_count++] = u;
        return true;
    }

    bool sendEmail( string t_address, string content){
        Mail* m = new Mail(currentUser->getAddress(),t_address,content);
        mails[mail_count++] = m;
        return true;
    }

    bool Login(string u_address, string u_password){
        for(int i=0;i<user_count;i++){
            if(users[i]->getAddress()==u_address){
                if(users[i]->getPassword()==u_password){
                    currentUser = users[i];
                    return true;
                }
                else return false;
            }
        }
        return false;
    }

    bool showSentEmails(){
        if(!currentUser) return false;
        int count = 0;
        for(int i=0;i<mail_count;i++){
            if(mails[i]->getFAddress()==currentUser->getAddress()){
                cout<<count<<" =>"<<endl;
                cout<<"*************************************************"<<endl;
                cout<<"From : "<<mails[i]->getFAddress()<<endl;
                cout<<"To : "<<mails[i]->getTAddress()<<endl;
                cout<<"\nContent : \n"<<mails[i]->getContent()<<endl;
                cout<<"*************************************************"<<endl;
                count++;
            }
        }
        return true;
    }

    bool showReceivedEmails(){
        if(!currentUser) return false;
        int count = 0;
        for(int i=0;i<mail_count;i++){
            if(mails[i]->getTAddress()==currentUser->getAddress()){
                cout<<count<<" =>"<<endl;
                cout<<"*************************************************"<<endl;
                cout<<"From : "<<mails[i]->getFAddress()<<endl;
                cout<<"To : "<<mails[i]->getTAddress()<<endl;
                cout<<"\nContent : \n"<<mails[i]->getContent()<<endl;
                cout<<"*************************************************"<<endl;
                count++;
            }
        }
        return true;
    }

    string getCurrentName(){return currentUser->getName();}

    void logout(){
        currentUser = NULL;
    }
};

int Mail::m_count = 1;
int User::u_count = 1;
int main(){
    Application App;
    bool flag = true;

    while(flag){
        system("cls");
        cout<<"Welcome to GMAIL!\n";
        cout<<"-----------------";
        int choice;
        cout<<"1.Login\n2.SignUp\nChoice : ";
        cin>>choice;
        if(choice==2){
            string name,address,password;
            cout<<"Enter your Name : ";
            cin>>name;
            cout<<"Enter your mail Address : ";
            cin>>address;
            cout<<"Enter your Password : ";
            cin>>password;
            App.signUp(name,address,password);
        }
        else if(choice==1){
            string address,password;
            cout<<"Enter your EMail-Address : ";
            cin>>address;
            cout<<"Enter your Password : ";
            cin>>password;
            if(App.Login(address,password)){
                cout<<"Login Successful\n";
                _getch();
                bool flag1 = true;
                while(flag1){
                    system("cls");
                    int choice1;
                    cout<<"Welcome "<<App.getCurrentName()<<"!"<<endl;
                    cout<<"1. Send Email\n2. View Recieved\n3. View Sent\n4.Logout\nChoice : ";
                    cin>>choice1;
                    
                    switch(choice1){
                        case 1:{
                            string address_t;
                            string content_t;
                            cout<<"Enter the Address to send : ";
                            cin>>address_t;
                            cout<<"Enter the Content : ";
                            cin>>content_t;
                            if(App.sendEmail(address_t,content_t)) cout<<"Mail sent successfully !"<<endl;
                            _getch();
                            break;
                        }
                        case 2:{
                            App.showReceivedEmails();
                            _getch();
                            break;
                        }
                        case 3:{
                            App.showSentEmails();
                            _getch();
                            break;
                        }
                        case 4:{
                            App.logout();
                            flag1 = false;
                            break;
                        }
                    }
                }
            }
        }
        else{
            flag = false;
        }
    }
}