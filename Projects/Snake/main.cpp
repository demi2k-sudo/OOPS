#include<bits/stdc++.h>
#include<ctime>
#include<stdlib.h>
using namespace std;



class node{
    public:
        int x;
        int y;
        node(int X,int Y){
            x = X;
            y = Y;
        }
};

char board[5][5];
vector<node> snake;

void printBoard(){
    for(auto i:snake){
        board[i.x][i.y] = '*';
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

void initialize(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            board[i][j] = ' ';
        }
    }
    
    int nx = rand()%5;
    int ny = rand()%5;
    while(board[nx][ny]!=' '){
        nx = rand()%5;
        ny = rand()%5;
    }   
    board[nx][ny] = 'X';
    node n(0,0);
    snake.push_back(n);
}

void move(int x,int y){
    if(x<5 and y<5 and board[x][y]!='*'){
        node n(x,y);
        node tail = snake[0];
        int cx,cy;
        cx = tail.x;
        cy = tail.y;
        board[cx][cy] = ' ';
        if(board[x][y]!='X') {
            snake.erase(snake.begin());
        }
        else{
            board[x][y] = ' ';
            int nx = rand()%5;
            int ny = rand()%5;
            while(board[nx][ny]!=' '){
                nx = rand()%5;
                ny = rand()%5;
            }   
            board[nx][ny] = 'X';
        }
        snake.push_back(n);
    }
    else{
        cout<<"\nGAME OVER!!!";
        exit(0);
    }
}

int main(){
    srand(time(0));
    initialize();
    int x=0,y=0;
    while(1){
        system("cls");
        printBoard();
        int choice;
        cout<<"Enter choice (8/4/5/6): ";
        cin>>choice;
        switch(choice){
            case 8:{
                move(--x,y);
                break;
            }
            case 5:{
                move(++x,y);
                break;
            }
            case 4:{
                move(x,--y);
                break;
            }
            case 6:{
                move(x,++y);
                break;
            }
        }
    }
}