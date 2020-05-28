//广度优先
#include<iostream>
#include<cstring>
#include<queue>
#include<set>
#include<vector>
using namespace std;
char jar[30][30];
int n,m,t,ans=0;
int direction[4][2]={-1,0,0,1,1,0,0,-1};
set<char> keybox;
bool judge(int y,int x){
    if (!(x > -1 && x<m && y>-1 && y < n)) return false;
    //  ^   *   .   a   A   @
    if (jar[y][x] == '*')  return false;
    else if (jar[y][x] > 64 && jar[y][x] < 75) {
        if (keybox.find(jar[y][x]) != keybox.end())  return true;
        else   return false;
    }
    else    return true;
}
void findwayout(int y,int x){
    queue<vector<int>> temp;
    vector<int> init={y,x,0,-1};
    temp.push(init);
    while (!temp.empty())
    {
        int bdc=0,r;
        vector<int> tv=temp.front();
        temp.pop();
        if(tv[2]>=t)    continue;
        if(jar[tv[0]][tv[1]]=='^'){
            ans=tv[2];
            break;
        }else if(jar[tv[0]][tv[1]]>96&&jar[tv[0]][tv[1]]<107){
            keybox.insert(jar[tv[0]][tv[1]]-32);
            bdc++;
        }
        for(int i=0;i<4;i++){
            if(i%2!=tv[3]%2||i==tv[3]){
                if(judge(tv[0]+direction[i][0],tv[1]+direction[i][1])){
                    temp.push({tv[0]+direction[i][0],tv[1]+direction[i][1],tv[2]+1,i});
                }else   bdc++;
            }else   r=i;
        }
        if(bdc==4)  temp.push({tv[0]+direction[r][0],tv[1]+direction[r][1],tv[2]+1,r});
    }
}
int main(){
    ios::sync_with_stdio(false);
    freopen("test.in", "r", stdin);
    freopen("test.out", "w+", stdout);
    while (cin >> n >> m >> t)
    {
        int initx,inity;
        for(int i=0;i<n;i++){
            cin >> jar[i];
            if(strchr(jar[i],'@')!=NULL){
                initx=strchr(jar[i],'@')-jar[i];
                inity=i;
            }
        }
        findwayout(inity,initx);
        if(ans) cout << ans << endl;
        else    cout << -1 << endl;
        ans=0;
        keybox.clear();
    }
    
}