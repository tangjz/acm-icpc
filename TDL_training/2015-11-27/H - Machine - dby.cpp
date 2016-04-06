#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 10030;
int w[MAXN],f[MAXN],tot[MAXN],son[MAXN][2],n;

inline int max(int a,int b){return a < b ? b : a;}
void read(int &x){
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
}
int main(){
	while(scanf("%d",&n) != EOF){
		for(int i = 2;i <= n;++ i){//scanf("%d",&f[i]),tot[i] = 0;
			read(f[i]);
			tot[i] = 0;
		}
		tot[1] = 0;
		for(int i = n;i >= 1;-- i){
			if(tot[i] == 0) w[i] = 1;
			else if(tot[i] == 1) w[i] = son[i][0];
			else{
				int a = son[i][0],b = son[i][1];
				if(a > b) w[i] = max(b + 1,a);
				else w[i] = max(a + 1,b);
			}
			son[f[i]][tot[f[i]] ++] = w[i];
		}
		printf("%d\n",w[1]);
	}	
	return 0;
}
