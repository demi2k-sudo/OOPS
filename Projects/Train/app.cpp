#include<iostream>
#include<queue>
#include<unordered_map>
#include<conio.h>
using namespace std;


class ticket{
    private:
        int ticket_id;
        string name;
        int age;
        string preference;
        string status;
        static int count;

    public:
        void setData( string n, int a, string p, string s){
            ticket_id = count;
            name = n;
            age = a;
            preference = p;
            status = s;
            count++;
        }

        ticket(){
            ticket_id = -1;
            name = "";
            age = -1;
            preference = "";
            status = "";
        }

        int getTicketId(){
            return ticket_id;
        }

        string getName(){
            return name;
        }

        int getAge(){
            return age;
        }

        string getPreference(){
            return preference;
        }

        string getStatus(){
            return status;
        }

        void setStatus(string s){
            status = s;
        }

        void display(){
            cout<<"-----------"<<endl;
            cout<<"Ticket Id: "<<ticket_id<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Age: "<<age<<endl;
            cout<<"Preference: "<<preference<<endl;
            cout<<"Status: "<<status<<endl;
            cout<<"-----------"<<endl;
        }
};

class Railways{
    private:

        queue<ticket> RAC;
        queue<ticket> WL;
        unordered_map<int, ticket> L;
        unordered_map<int, ticket> M;
        unordered_map<int, ticket> U;

    public:
        static int available_L;
        static int available_M;
        static int available_U;
        static int available_RAC;
        static int available_WL;

        unordered_map<int,ticket> getL(){
            return L;
        }

        unordered_map<int,ticket> getM(){
            return M;
        }

        unordered_map<int,ticket> getU(){
            return U;
        }

        bool book(ticket t){
            if(t.getPreference() == "L" && available_L > 0){
                t.setStatus("booked");
                L[t.getTicketId()]=t;
                cout<<"Your ticket has been booked successfully in Lower Berth"<<endl;
                available_L--;
                return true;
            }
            else if(t.getPreference() == "M" && available_M > 0 ){
                t.setStatus("booked");
                M[t.getTicketId()]=t;
                cout<<"Your ticket has been booked successfully in Middle Berth"<<endl;
                available_M--;
                return true;
            }
            else if(t.getPreference() == "U" && available_U > 0 ){
                t.setStatus("booked");
                U[t.getTicketId()]=t;
                cout<<"Your ticket has been booked successfully in Upper Berth"<<endl;
                available_U--;
                return true;
            }
            else if(available_L>0){
                t.setStatus("booked");
                L[t.getTicketId()]=t;
                cout<<"Your ticket has been booked successfully in Lower Berth"<<endl;
                available_L--;
                return true;
            }
            else if(available_M > 0 ){
                t.setStatus("booked");
                M[t.getTicketId()]=t;
                cout<<"Your ticket has been booked successfully in Middle Berth"<<endl;
                available_M--;
                return true;
            }
            else if(available_U > 0 ){
                t.setStatus("booked");
                U[t.getTicketId()]=t;
                cout<<"Your ticket has been booked successfully in Upper Berth"<<endl;
                available_U--;
                return true;
            }
            else if(available_RAC > 0 ){
                t.setStatus("RAC");
                cout<<"Your ticket has been booked in RAC"<<endl;
                RAC.push(t);
                available_RAC--;
                return true;
            }
            else if(available_WL > 0){
                t.setStatus("waiting list");
                cout<<"Your ticket has been booked in Waiting List"<<endl;
                WL.push(t);
                available_WL--;
                return true;
            }
            else{
                return false;
            }
        }

        void cancel(int id){
            int free = 0;
            if(L.find(id) != L.end()){
                L.erase(id);
                available_L++;
                free=1;
            }
            else if(M.find(id) != M.end()){
                M.erase(id);
                available_M++;
                free=2;
            }
            else if(U.find(id) != U.end()){
                U.erase(id);
                available_U++;
                free=3;
            }
            if(!RAC.empty()){
                ticket t = RAC.front();
                RAC.pop();
                available_RAC++;
                if(!WL.empty()){
                    ticket w = WL.front();
                    WL.pop();
                    RAC.push(w);
                    available_WL++;
                    available_RAC--;
                }
                book(t);
            }                      
        }
};

int Railways::available_L=1;
int Railways::available_M=1;
int Railways::available_U=1;
int Railways::available_RAC=1;
int Railways::available_WL=1;
int ticket::count=1;
int main(){
    int choice;
    Railways mgmt;
    bool start = true;
    unordered_map<int,ticket> temp;
    while(start){
        system("cls");
        cout<<"=====RAILWAY MANAGEMENT SYSTEM=====";
        cout<<"\n1.Show Available Seats\n2.Book_Ticket\n3.Cancel Ticket\n4.Show booked";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:{
                cout<<"\nAvailable Lower Berth: "<<Railways::available_L;
                cout<<"\nAvailable Middle Berth: "<<Railways::available_M;
                cout<<"\nAvailable Upper Berth: "<<Railways::available_U;
                cout<<"\nAvailable RAC: "<<Railways::available_RAC;
                cout<<"\nAvailable Waiting List: "<<Railways::available_WL<<endl;
                _getch();
                break;
            }
            case 2:{
                string name;
                int age;
                string preference;
                cout<<"Enter your Name: ";
                cin>>name;
                cout<<"Enter your Age: ";
                cin>>age;
                cout<<"Enter your Preference(L/M/U): ";
                cin>>preference;
                ticket t;
                t.setData( name, age, preference, "");
                bool res = mgmt.book(t);
                if(!res){
                    cout<<"No seats available"<<endl;
                }
                else{
                    cout<<"Your ticket ID is "<<t.getTicketId()<<endl;
                }
                
                _getch();
                break;
            }
            case 3:{
                int id;
                cout<<"Enter your ID: ";
                cin>>id;
                mgmt.cancel(id);
                _getch();
                break;
            }
            case 4:{
                cout<<"=====Booked Tickets====="<<endl;
                for(auto i: mgmt.getL()){
                    i.second.display();
                }
                for(auto i: mgmt.getM()){
                    i.second.display();
                }
                for(auto i: mgmt.getU()){
                    i.second.display();
                }
                _getch();
                break;
            }
            
    }
    }
    return 0;
}

