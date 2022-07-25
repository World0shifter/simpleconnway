#include <iostream>
#include <fstream>
#include <cstdlib> // needed for system("clear") and system(timeout)
#include <queue>

using namespace std;

const int board_size=32;
int tabla[board_size][board_size*2];

int dx[]={0,1,0,-1,1,-1,1,-1};  //movement vectors for 8 directions
int dy[]={1,0,-1,0,1,-1,-1,1};

struct grid{ //holds coords for grid place to be updated and the value to update it to
    int a,b;
    bool on;
};

queue<grid> update; //stores the coords and values of all grid places to update

int neighbors(int x, int y){ //find out and return number of alive neighbors
    int nr=0;
    for(int i=0; i<8; i++){
        if(tabla[x+dx[i]][y+dy[i]]){
            nr++;
        }
    }
    return nr;
}

void read(){ // read starting positions from file
    ifstream in("start.in");
    int a,b;
    while(in>>a>>b){
        tabla[a][b]=1;
    }
}

void update_grid(){ // update the grid after it has been displayed
    while(!update.empty()){
        grid x=update.front();
        update.pop();
        tabla[x.a][x.b]=x.on;
    }
}

int main()
{
    read();
    int v=0;
    grid casting; // used to put values into the queue
    while(true){
        for(int i=1; i<=board_size-2; i++){
            for(int j=1; j<=2*board_size-4; j++){
                v=0;
                if(tabla[i][j]){
                    cout<<"#";
                }else{
                    cout<<"-";
                }
                v=neighbors(i,j);
                if(v==3){
                    casting.a=i;
                    casting.b=j;
                    casting.on=true;
                    if(!tabla[i][j]){
                        update.push(casting);
                    }
                }
                if(v<2 || v>3){
                    casting.a=i;
                    casting.b=j;
                    casting.on=false;
                    update.push(casting);
                }
            }
            cout<<"\n";
        }
        system("timeout 1 > NUL"); // wait a second so the grid can be seen
        system("cls"); // clear the console
        update_grid();
    }
    return 0;
}
