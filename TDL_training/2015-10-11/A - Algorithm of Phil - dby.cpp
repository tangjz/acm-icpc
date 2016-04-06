#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int Mod = 1000000007;
const int MAXN = 100030;
char s[MAXN],out[MAXN];
int n,l,r;

int main(){
	int TT;
	scanf("%d",&TT);
	for(int Cas = 1;Cas <= TT;++ Cas){
		printf("Case #%d: ",Cas);
		scanf("%s",s);
		int n = strlen(s);
		int cnt = 0;
		if(n & 1){
			out[cnt ++] = s[((n + 1) >> 1) - 1];
			l = (n >> 1) - 1; r = (n + 1) >> 1;
		}else{
			l = (n >> 1) - 1; r = n >> 1;
		}
		while(l >= 0 && r < n){
			if(s[l] - '0' > s[r] - '0'){
				out[cnt ++] = s[l]; out[cnt ++] = s[r];
			}else{
				out[cnt ++] = s[r]; out[cnt ++] = s[l];
			}
			-- l; ++ r;
		}
		int ret = 0;
		for(int i = 0;i < n;++ i)
			ret = ((ret << 1) + (out[i] - '0')) % Mod;
		printf("%d\n",ret);
	}
	return 0;
}
