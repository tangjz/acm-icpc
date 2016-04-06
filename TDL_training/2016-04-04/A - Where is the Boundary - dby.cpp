#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 10000 + 4,MAXM = 100 + 3;
int n,m;
char buf[MAXM][MAXN];

int main(){
    scanf("%d%d",&n,&m);
    int ret = 0,l = 0,r = 1;
    for(int i = 0;i < m;++ i){
        scanf("%s",buf[i]);
        for(int j = 0;j < n;++ j)
        if(buf[i][j] == 'W')
            ++ ret;
    }
    int tmp = ret;
    for(int i = 1;i <= n;++ i){
        for(int j = 0;j < m;++ j){
            if(buf[j][i - 1] == 'W')
                -- tmp;
            else
                ++ tmp;
        }
        if(tmp < ret){
            ret = tmp;
            l = i; r = i + 1;
        }
    }
    printf("%d %d\n",l,r);
    return 0;
}
