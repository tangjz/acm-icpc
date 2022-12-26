#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXM = 100,MAXT = 330;
int n,m,k,l[MAXM],r[MAXM],c[MAXM],ord[MAXM],sum[MAXT];

inline bool cmp(int x,int y){
	if(r[x] == r[y]) return l[x] < l[y];
	else return r[x] < r[y];
}
inline long long calc(int x,int tot,int cur){
	if(x > tot) return (long long)sum[tot] + (long long)(x - tot) * cur;
	else return sum[x];
}
void dfs(int far,int co,int prel,int cur){
	if(far == n){
		sum[co] = co; return;
	}
	for(int i = cur;i < m;++ i){
		int now = ord[i];
		if(l[now] <= far + 1 && l[now] > prel && r[now] > far)
			dfs(r[now],co + c[now],far + 1,i + 1);
	}
}
int main(){
	int TT;
	scanf("%d",&TT);
	for(int Cas = 1;Cas <= TT;++ Cas){
		printf("Case #%d: ",Cas);
		scanf("%d%d%d",&n,&m,&k);
		int tot = 0;
		for(int i = 0;i < m;++ i){
			scanf("%d%d%d",&l[i],&r[i],&c[i]); ord[i] = i;
			tot += c[i];
		}
		sort(ord,ord + m,cmp);
		for(int i = 0;i <= tot;++ i) sum[i] = -1;
		dfs(0,0,0,0);
		int cur = 0;
		for(int i = 1;i <= tot;++ i)
		if(sum[i] != -1)
			cur = i,sum[i] += sum[i - 1];
		else sum[i] = sum[i - 1] + cur;
		long long ret = 0LL;
		for(int x,y,i = 0;i < k;++ i){
			scanf("%d%d",&x,&y);
			ret += calc(y,tot,cur) - calc(x - 1,tot,cur);
		}
		printf("%lld\n",ret);
	}
	return 0;
}
