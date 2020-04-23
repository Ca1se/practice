#include<iostream>
using namespace std;
static int cube[100][100][100];
int main(){
    ios::sync_with_stdio(false);
    int x,y,z,n,count=0;
    cin >> x >> y >> z >> n;
    for(int i=0;i<n;i++){
        int xi,yi,zi;
        cin >> xi >> yi >> zi;
        cube[xi][yi][zi]=1;
    }
    for(int j=y;j>0;j--){
        for(int i=1;i<x+1;i++){
            int judge=0;
            for(int k=z;k>0;k--){
                if(cube[i][j][k]){
                    judge=1;
                    break;
                }
            }
            if(judge)
                cout << "x";
            else
                cout << ".";
        }
        cout << " ";
        for(int k=1;k<z+1;k++){
            int judge=0;
            for(int i=x;i>0;i--){
                if(cube[i][j][k]){
                    judge=1;
                    break;
                }
            }
            if(judge)
                cout << "x";
            else
                cout << ".";
        }
        cout << "\n";
    }
    for(int k=1;k<z+1;k++){
        for(int i=1;i<x+1;i++){
            int judge=0;
            for(int j=1;j<y+1;j++){
                if(cube[i][j][k]){
                    judge=1;
                    break;
                }
            }
            if(judge)
                cout << "x";
            else
                cout << ".";
        }
        cout << "\n";
    }
}