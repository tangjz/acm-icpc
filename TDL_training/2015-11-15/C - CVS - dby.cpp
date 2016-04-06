#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int MAXN = 500300,MAXMEM = MAXN * 2;
int n,m,tag[MAXMEM],dtag[MAXMEM],fa[MAXMEM],dfa[MAXMEM],mem,dmem,tot,p[MAXN],dp[MAXN];
char cmd[30];

void read(int &x){
	char c;
	while((c = getchar()) < '0' || c > '9');
	x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
}
int main(){
	scanf("%d%d",&n,&m);
		tag[mem = 0] = 0;
		p[tot = 1] = mem ++; dp[tot] = 0;
		for(int i = 0,id,crs;i < n;++ i){
			scanf("%s",cmd);
			read(id);
			if(cmd[0] == 'l' && cmd[1] == 'e'){
				read(crs);//scanf("%d",&crs);
				tag[mem] = crs;
				fa[mem] = p[id];
				p[id] = mem ++;  dp[id] = 0;
			}else if(cmd[0] == 'r' && cmd[1] == 'o'){
				dtag[dmem] = tag[p[id]]; dfa[dmem] = dp[id];
				p[id] = fa[p[id]]; dp[id] = dmem ++;
			}else if(cmd[0] == 'r' && cmd[1] == 'e'){
				tag[mem] = dtag[dp[id]]; fa[mem] = p[id];
				dp[id] = dfa[dp[id]]; p[id] = mem ++;
			}else if(cmd[0] == 'c' && cmd[1] == 'l'){
				p[++ tot] = p[id]; dp[tot] = dp[id];
			}else{
				if(tag[p[id]]) printf("%d\n",tag[p[id]]);
				else puts("basic");
			}
		}
	return 0;
}
