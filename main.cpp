#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>

using namespace std;

const int marime=32;
int tabla[marime][marime+marime];
int dx[]={0,1,0,-1,1,-1,1,-1};
int dy[]={1,0,-1,0,1,-1,-1,1};
struct grid{
    int a,b;
    bool on;
};
queue<grid> update;

int vecini(int x, int y){
    int nr=0;
    for(int i=0; i<8; i++){
        if(tabla[x+dx[i]][y+dy[i]]){
            nr++;
        }
    }
    return nr;
}

void read(){
    ifstream in("pozitii.in");
    int a,b;
    while(in>>a>>b){
        tabla[a][b]=1;
    }
}

void update_grid(){
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
        for(int i=1; i<=marime-2; i++){
            for(int j=1; j<=2*marime-4; j++){
                v=0;
                if(tabla[i][j]){
                    cout<<"#";
                }else{
                    cout<<"-";
                }
                v=vecini(i,j);
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
        system("timeout 1 > NUL");
        system("cls");
        update_grid();
    }
    return 0;
}
