#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXD = 30,MAXN = 103,oo = ~0U>>2;
char s[MAXN];
int B,f[MAXN],p[MAXD][MAXN],c[MAXD][MAXN],cnt[MAXD];

int main(){
	int TT;
	scanf("%d",&TT);
	for(int Cas = 1;Cas <= TT;++ Cas){
		scanf("%s%d",s,&B);
		printf("Case #%d: ",Cas);
		int n = strlen(s);
		for(int i = 1;i <= B;++ i) f[i] = oo;
		f[0] = 0;
		for(int i = 0;i < 26;++ i){
			scanf("%d",&cnt[i]);
			for(int j = 0;j < cnt[i];++ j) scanf("%d%d",&p[i][j],&c[i][j]);
		}
		for(int i = 0;i < n;++ i)
			for(int j = B;j;-- j){
				int ch = s[i] - 'a',dt = 0;
				for(int k = 0;k < cnt[ch];++ k)
				if(j % p[ch][k] == 0)
					dt += j / p[ch][k] * c[ch][k];
				if(dt + f[j - 1] < f[j])
					f[j] = f[j - 1] + dt;
			}
		printf("%d\n",f[B]);
	}
	return 0;
}
