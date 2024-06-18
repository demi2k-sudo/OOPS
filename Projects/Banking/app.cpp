#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<conio.h>
using namespace std;


class Customer{
    private:
        int custId;
        int accountNo;
        string name;
        double balance;
        string password;
        static int customer_count;
    public:
        Customer(int custId_a,int accountNo_a, string name_a, double balance_a, string password_a, bool updateCount){
            custId = custId_a;
            accountNo = accountNo_a;
            name = name_a;
            balance = balance_a;
            password = password_a;
            if(updateCount)
            customer_count+=1;
        }

        Customer(){
            custId = 0;
            accountNo = 0;
            name = " ";
            balance = 0;
            password = " ";
        }

        Customer(string name_a, string password_a){
            custId = ++customer_count*100;
            accountNo = customer_count*1000;
            name = name_a;
            balance = 10000;
            password = password_a;
        }

        void reset(string name_a, string password_a){
            custId = ++customer_count*100;
            accountNo = customer_count*1000;
            name = name_a;
            balance = 10000;
            password = password_a;
        }

        int getCustId(){
            return custId;
        }

        int getAccountNo(){
            return accountNo;
        }

        string getName(){
            return name;
        }

        string getPassword(){
            return password;
        }

        double getBalance(){
            return balance;
        }

        void setBalance(double balance_a){
            balance = balance_a;
        }

        void display(){
            cout<<"Customer ID: "<<custId<<endl;
            cout<<"Account Number: "<<accountNo<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Balance: "<<balance<<endl;
        }
};

class Transaction{
    private:
        int transaction_id;
        string type;
        double amount;
        double balance;

    public:
        void setData(int id, string type_a, double amount_a, double balance_a){
            transaction_id = id;
            type = type_a;
            amount = amount_a;
            balance = balance_a;
        }
        
        int getId(){
            return transaction_id;
        }

        string getType(){
            return type;
        }

        double getAmount(){
            return amount;
        }

        double getBalance(){
            return balance;
        }

};

int Customer::customer_count = 0;

bool logTransaction(int CustId, Transaction t){
    fstream file(to_string(CustId)+".txt", ios::app);
    if(file.is_open()){
        file<<t.getId()<<" "<<t.getType()<<" "<<t.getAmount()<<" "<<t.getBalance()<<endl;
        file.close();
        return true;
    }
    return false;
}


vector<string> read(const string &fname){
    fstream file(fname);
    vector<string> data;
    string line;

    while(file.is_open()){
        while(getline(file,line)){
            data.push_back(line);
        }
        file.close();
    }
    return data;
}

bool file_append(const string& fname, string data){
    fstream file(fname, ios::app);
    if(file.is_open()){
        file<<data<<endl;
        file.close();
        return true;
    }
    return false;
}

vector<Customer> initialize(){
    vector<string> data = read("bank_db.txt");
    int custId,accountNo;
    double Balance;
    string name,password;
    vector<Customer> customers;

    for(int i=0;i<data.size();i++){
        stringstream ss(data[i]);
        ss>>custId>>accountNo>>name>>Balance>>password;
        customers.push_back(Customer(custId,accountNo,name,Balance,password,true));
    }
    return customers;
}

unordered_map<int,Customer> initializeHashMap(){

    vector<string> data = read("bank_db.txt");
    int custId,accountNo;
    double Balance;
    string name,password;
    unordered_map<int,Customer> customers;

    for(int i=0;i<data.size();i++){
        stringstream ss(data[i]);
        ss>>custId>>accountNo>>name>>Balance>>password;
        customers[custId] = Customer(custId, accountNo, name, Balance, password, false);
    }
    return customers;
}

unordered_map<int,Customer> initializeAccountMap(){

    vector<string> data = read("bank_db.txt");
    int custId,accountNo;
    double Balance;
    string name,password;
    unordered_map<int,Customer> customers;

    for(int i=0;i<data.size();i++){
        stringstream ss(data[i]);
        ss>>custId>>accountNo>>name>>Balance>>password;
        customers[accountNo] = Customer(custId, accountNo, name, Balance, password, false);
    }
    return customers;
}

string encrypt(string s){
    for(int i = 0 ; i<s.length(); i++){
        if(s[i]>='0' and s[i]<='9'){
            //code to shift one
            s[i] = (s[i]-'0'+1)%10+'0';
        }
        if(s[i]>='a' and s[i]<='z'){
            //code to shift one
            s[i] = (s[i]-'a'+1)%26+'a';
        }
        if(s[i]>='A' and s[i]<='Z'){
            //code to shift one
            s[i] = (s[i]-'A'+1)%26+'A';
        }
    }
    return s;
}

string decrypt(string s){
    for(int i = 0 ; i<s.length(); i++){
        if(s[i]>='0' and s[i]<='9'){
            //code to shift one
            s[i] = (s[i]-'0'-1+10)%10+'0';
        }
        if(s[i]>='a' and s[i]<='z'){
            //code to shift one
            s[i] = (s[i]-'a'-1+26)%26+'a';
        }
        if(s[i]>='A' and s[i]<='Z'){
            //code to shift one
            s[i] = (s[i]-'A'-1+26)%26+'A';
        }
    }
    return s;
}

void backup(unordered_map<int,Customer> accountMap){
    vector<Customer> newData;
    for(auto i:accountMap){
        newData.push_back(i.second);
    }
    fstream file("bank_db.txt",::ios::out);
    for(auto i:newData){
        file<<i.getCustId()<<" "<<i.getAccountNo()<<" "<<i.getName()<<" "<<i.getBalance()<<" "<<i.getPassword()<<"\n";
    }
    file.close();

}

int readCount(const string &fname){
    fstream file(fname);
    vector<string> data;
    string line;

    while(file.is_open()){
        while(getline(file,line)){
            data.push_back(line);
        }
        file.close();
    }
    return data.size();
}



int main(){
    vector<Customer> customers = initialize();
    unordered_map<int, Customer> customerMap = initializeHashMap();
    unordered_map<int, Customer> accountMap = initializeAccountMap();
    int choice;
    int custId,accountNo;
    double Balance;
    string name,password,pwd_chk;
    Customer new_customer;
    int i;
    bool start = true;
    Transaction t;
    while(start){
        system("cls");
        cout<<"====BANKING APPLICATION===="<<endl;
        cout<<"1.Login\n2.SignUp\n3.Exit\nChoice :";
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Enter your Customer ID :";
                cin>>custId;
                cout<<"Enter your password :";
                cin>>password;
                if(customerMap.find(custId)!=customerMap.end()){
                    if(decrypt(customerMap[custId].getPassword()) == password){
                        cout<<"Login Successful!\n";
                        customerMap[custId].display();
                        Customer cus = customerMap[custId];
                        double amount;
                        Customer other;
                        vector<string> data;
                        bool loop = true;
                        while(loop){
                            system("cls");
                            cout<<"1.Withdraw\n2.Deposit\n3.Check Balance\n4.Display Details\n5.Transfer funds\n6.Check History\n7.Logout\nChoice :";
                            cin>>choice;
                            switch(choice){
                                case 1:
                                    cout<<"Enter the amount to withdraw :";
                                    cin>>amount;
                                    if(amount>cus.getBalance()) cout<<"Insufficient Balance!\n";
                                    else{
                                        i = readCount(to_string(cus.getCustId())+".txt");
                                        t.setData(i+1, "Debit", amount, cus.getBalance()-amount);
                                        logTransaction(cus.getCustId(), t);
                                        cus.setBalance(cus.getBalance()-amount);
                                        cout<<"Amount withdrawn successfully!\n";
                                    }
                                    customerMap[cus.getCustId()] = cus;
                                    accountMap[cus.getAccountNo()] = cus; 
                                    backup(accountMap);
                                    _getch();
                                    break;
                                case 2:
                                    cout<<"Enter the amount to deposit :";
                                    cin>>amount;
                                    i = readCount(to_string(cus.getCustId())+".txt");
                                    t.setData(i+1, "Deposit", amount, cus.getBalance()+amount);
                                    logTransaction(cus.getCustId(), t);
                                    cus.setBalance(cus.getBalance()+amount);
                                    cout<<"Amount deposited successfully!\n";
                                    customerMap[cus.getCustId()] = cus;
                                    accountMap[cus.getAccountNo()] = cus;
                                    backup(accountMap);
                                    _getch();
                                    break;
                                case 3:
                                    cout<<"Your current balance is :"<<cus.getBalance()<<endl;
                                    _getch();
                                    break;
                                case 4:
                                    cus.display();
                                    _getch();
                                    break;
                                case 5:
                                    int accNo;
                                    cout<<"Enter the Account Number that you want to transfer your funds to : ";
                                    cin>>accNo;
                                    other = accountMap[accNo];
                                    if(other.getCustId()!=0){
                                        cout<<"Enter the amount you want to transfer :";
                                        cin>>amount;
                                        if(amount>cus.getBalance()) cout<<"Insufficient Balance!\n";
                                        else{
                                            i = readCount(to_string(cus.getCustId())+".txt");
                                            t.setData(i+1, "Debit", amount, cus.getBalance()-amount);
                                            logTransaction(cus.getCustId(), t);
                                            cus.setBalance(cus.getBalance()-amount);
                                            i = readCount(to_string(other.getCustId())+".txt");
                                            t.setData(i+1, "Deposit", amount, other.getBalance()+amount);
                                            logTransaction(other.getCustId(), t);
                                            other.setBalance(other.getBalance()+amount);
                                            cout<<"Amount transferred successfully!\n";
                                        }
                                        customerMap[cus.getCustId()] = cus;
                                        accountMap[cus.getAccountNo()] = cus;
                                        customerMap[other.getCustId()] = other;
                                        accountMap[other.getAccountNo()] = other;
                                        backup(accountMap);
                                    }
                                    else{
                                        cout<<"Account not found !"<<endl;
                                    }
                                    _getch();
                                    break;
                                
                                case 6:
                                    data = read(to_string(cus.getCustId())+".txt");
                                    cout<<"Transaction History :"<<endl;
                                    cout<<"ID\tType\tAmount\tBalance"<<endl;
                                    for(auto i:data){
                                        cout<<i<<endl;
                                    }
                                    _getch();
                                    break;                                    
                                
                                case 7:
                                    loop = false;
                                    cout<<"bye........:("<<endl;
                                    break;
                                    
                            }
                        }
                    }
                    else cout<<"Invalid Credentials!\n";
                }
                else cout<<"Customer not found!\n";
                _getch();
                
                break;

            case 2:
                cout<<"Enter your Name :";
                cin>>name;
                while(1){
                    cout<<"Enter your new password :";
                    cin>>password;
                    cout<<"Re Enter your password :";
                    cin>>pwd_chk;
                    if(pwd_chk == password) break;
                    else cout<<"Passwords doesn't match !\n";
                }          
                new_customer.reset(name,encrypt(password));
                customerMap[new_customer.getCustId()] = new_customer;
                customers.push_back(new_customer);
                
                if(file_append("bank_db.txt", to_string(customers[customers.size()-1].getCustId())
                +" "+to_string(customers[customers.size()-1].getAccountNo())+" "
                +customers[customers.size()-1].getName()+" "
                +to_string(customers[customers.size()-1].getBalance())
                +" "+customers[customers.size()-1].getPassword())) cout<<"DB Updated Successfully!\n";
                cout<<"Remember the given customer ID that you'll be using to login :)\n";
                new_customer.display();
                _getch();
                break;

            case 3:
                cout<<"Thank you for using our service !"<<endl;
                start = false;
                break;

        }
    }

    return 0;
}

