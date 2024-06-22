#include<iostream>
#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

class Taxi{
    int id;
    int fare;
    double earnings;

    public:
        Taxi(int i, int f){
            id = i;
            fare = f;
            earnings = 0;
        }

        void display(){
            cout<<"Taxi "<<id<<"\tRs "<<fare<<"\t"<<earnings<<endl;
        }

        bool operator <(const Taxi& t) const{
            return earnings < t.earnings;
        }

        void addEarnings(int dist){
            cout<<"Taxi Alloted : "<<id<<endl;
            dist*=5;
            if(dist<5){
                earnings+=dist*10;
                cout<<"Cost : "<<dist*10<<endl;
            }
            else{
                earnings+=50+dist*20;
                cout<<"Cost : "<<50+dist*20<<endl;
            }
            cout<<"You have arrived at your location !"<<endl;
        }
};

class TaxiCity{
    map<char,set<Taxi>> GMap;
    vector<char> city = {'A','B','C','D','E'};
    int num_taxis;
    static int count;

    public:

        TaxiCity(int num){
            num_taxis = num;
            for(int i=0;i<num_taxis;i++){
                addTaxi(rand()%200+10);
            }
        }

        void addTaxi(int fare) {
            GMap[city[rand()%city.size()]].insert(Taxi(count++,fare));
        }

        void showTaxis(){
            for(auto c: city){
                cout<<c<<" : \n";
                for(auto t: GMap[c]){
                    t.display();
                }
                cout<<endl;
            }
        }

        void bookTaxi(){
            char loc;
            cout<<"Enter your location :";
            cin>>loc;
            int ind,d;
            char dest;
            cout<<"Where do you wanna go :";
            cin>>dest;
            for(int i = 0; i<city.size(); i++){
                if(city[i]==loc){
                    ind = i;
                }
            }
            for(int i = 0; i<city.size(); i++){
                if(city[i]==dest){
                    d = i;
                }
            }
            
            int l=ind,r=ind;
            while(l>=0 and r<city.size()){
                if(!(GMap[city[r]].empty())){
                    auto t = GMap[city[r]].begin();
                    Taxi temp = *t;
                    temp.addEarnings(abs(d-ind));
                    GMap[city[r]].erase(t);
                    GMap[dest].insert(temp);
                    break;
                }

                if(!(GMap[city[l]].empty())){
                    auto t = GMap[city[l]].begin();
                    Taxi temp = *t;
                    temp.addEarnings(abs(d-ind));
                    GMap[city[l]].erase(t);
                    GMap[dest].insert(temp);
                    break;
                }

                l--;
                r++;
            }

        }
};

int TaxiCity::count = 0;

int main(){    
    TaxiCity t(4);
    while(1){
        system("cls");
        cout<<"===== Welcome to Taxi City =====\n";
        cout<<"1. Show taxis\n2. Book Taxi\n3. Exit\n";
        int ch;
        cin>>ch;
        switch(ch){
            case 1:
                t.showTaxis();
                _getch();
                break;
            case 2:
                t.bookTaxi();
                _getch();
                break;
            case 3:
                exit(0);
        }
    }
    return 0;
}
