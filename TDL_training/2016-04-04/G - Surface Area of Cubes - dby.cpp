#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN = 1000 + 9,mx[] = {-1,1,0,0,0,0},my[] = {0,0,-1,1,0,0},mz[] = {0,0,0,0,-1,1};
ll A,B,C,ret;
int n,x[MAXN],y[MAXN],z[MAXN],dt[6];

bool chk(int i,int px,int py,int pz){
    if(px >= 0 && px < A && py >= 0 && py < B && pz >= 0 && pz < C){
        for(int j = 0;j < i;++ j)
        if(x[j] == px && y[j] == py && z[j] == pz)
            return false;
        return true;
    }else return false;
}

int main(){
    cin >> A >> B >> C >> n;
    ret = (A * B + A * C + B * C) * 2;
    for(int i = 0;i < n;++ i){
        scanf("%d%d%d",&x[i],&y[i],&z[i]);
        for(int j = 0;j < 6;++ j) dt[j] = -1;
        for(int k = 0;k < 6;++ k)
        if(chk(i,x[i] + mx[k],y[i] + my[k],z[i] + mz[k]))
            dt[k] = 1;
        for(int j = 0;j < 6;++ j) ret += dt[j];
    }
    cout << ret << endl;
    return 0;
}
