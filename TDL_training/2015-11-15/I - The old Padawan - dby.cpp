#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 100030,oo = ~0U>>2;
int n,m,k,t[MAXN],now;
long long s[MAXN];

inline long long max(long long a,long long b){return a > b ? a : b;}
int main(){
	while(scanf("%d%d%d",&n,&m,&k) != EOF){
		s[0] = 0;
		for(int x,i = 1;i <= n;++ i){
			scanf("%d",&x);
			s[i] = s[i - 1] + x;
		}
		t[0] = 0; t[m + 1] = oo;
		for(int i = 1;i <= m;++ i) scanf("%d",&t[i]);
		now = 0;
		for(int i = 1;i <= m + 1;++ i){
			/*
			printf("%d %d\n",now)
			*/
			if(t[i] - t[i - 1] > n - now){
				printf("%d\n",t[i - 1] + n - now);
				break;
			}
			int nxt = now + t[i] - t[i - 1] - 1;
			long long pre = max(s[nxt] - k - 1,0);
			int pos = upper_bound(s,s + nxt + 1,pre) - s - 1;
			now = pos;
		}
	}
	return 0;
}
