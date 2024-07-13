#include<iostream>
#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

/*
























Airways - name,flights

Flight - tickets,price,seatCount

*/

class Ticket{
    int ticket_id;
    string name;
    int age;
    double cost;
    int flight_id;

    public:

        Ticket(string name_a, int age_a){
            name = name_a;
            age = age_a;
        }

        Ticket(){
            
        }

        int getID(){
            return ticket_id;
        }

        void setCost(double c){
            cost = c;
        }

        void setFlightID(int f){
            flight_id = f;
        }

        void setTicketID(int t){
            ticket_id = t;
        }

        void getName(){
            cout<<name<<endl;
        }
        void getAge(){
            cout<<age<<endl;
        }

        void display(){
            cout<<ticket_id;
            cout<<"\t"<<name;
            cout<<"\t"<<age;
            cout<<"\t"<<cost;
            cout<<"\t"<<flight_id<<endl;
        }
};

class Flight{
    int flight_id;
    string name;
    map<int,Ticket> ticket_list;
    int available_seats;
    double price;

    public:

        Flight(){
            flight_id = 0;
            name = "";
            available_seats = 0;
            price = 0.0;
        }

        Flight(int id, string name_a, int total_seats, double price_a ){
            name = name_a;
            flight_id = id;
            available_seats = total_seats;
            price = price_a;
        }

        
        int book(Ticket t){
            if(available_seats){
                t.setCost(price);
                t.setFlightID(flight_id);
                t.setTicketID(flight_id*1000+available_seats);
                cout<<"You have to pay Rupees "<<price<<endl;
                price+=200;
                ticket_list[t.getID()] = t;
                cout<<"Your ticket ID : "<<t.getID()<<endl;
                available_seats--;
                return t.getID();
            }
            else cout<<"Seats unavailable!"<<endl;
            return 0;
        }

        void cancel(int id){
            ticket_list.erase(id);
            available_seats--;
            price-=200;
        }

        void display(){
            cout<<flight_id;
            cout<<"\t"<<name;
            cout<<"\t"<<available_seats;
            cout<<"\t\t"<<price<<endl;
        }

        void displayTickets(){
            for(auto i:ticket_list){
                i.second.display();
            }
        }
};


class Airlines{
    map <int,Flight> flights;
    map <int,int> tickets;
    int count=1;

    public:
        void addFlight(string name, int total_seats, double price){
            Flight f(count,name,total_seats,price);
            flights[count++] = f;
        }

        void bookTicket(){
            int f_id;
            cout<<"Enter the flight ID :";
            cin>>f_id;
            Flight &f = flights[f_id];
            string name;
            int age;
            cout<<"Enter your name :";
            cin>>name;
            cout<<"Enter your age :";
            cin>>age;
            int res = f.book(Ticket(name,age));
            if(res){
                tickets[res] = f_id;
                cout<<"Ticket booking successful !"<<endl;
            }
            else{
                cout<<"Ticket booking unsucessful !"<<endl;
            }
        }

        void cancelTicket(){
            int t_id;
            cout<<"Enter your train_id of the ticket :";
            cin>>t_id;
            int f_id = tickets[t_id];
            Flight &f = flights[f_id];
            f.cancel(t_id);
        }

        void displayFlights(){
            cout<<"ID\tName\tAvailable\tPrice"<<endl;
            for(auto i:flights){
                i.second.display();
            }
        }

        void displayTickets(){
            cout<<"ID\tName\tAge\tCost\tFlight ID"<<endl;
            for(auto i:flights){
                i.second.displayTickets();
            }
        }
};

int main(){
    Airlines Indigo;
    Indigo.addFlight("Aries",50,5000);
    Indigo.addFlight("Gemini", 40, 4000);
    Indigo.addFlight("Cancer", 30, 3000);
    Indigo.addFlight("Leo", 20, 2000);

    bool start = true;

    while(start){
        system("cls");
        cout<<"==AIRLINES INDIGO WELCOMES YOU==";
        cout<<"\n1.Show Flights\n2.Book Tickets\n3.Show booked Tickets\n4.Cancel Tickets\nChoice :";
        int choice;
        cin>>choice;
        switch(choice){
            case 1 : {
                Indigo.displayFlights();
                _getch();
                break;
            }
            case 2:
                Indigo.bookTicket();
                _getch();
                break;

            case 3:
                Indigo.displayTickets();
                _getch();
                break;
            
            case 4:
                Indigo.cancelTicket();
                _getch();
                break;

        }
    }


}