#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 35,MAXQ = MAXN * 300,MAXM = 1030;
const long long oo = (long long)1e11;
bool v[MAXN],in[MAXN];
int n,m,S,T,q[MAXQ];
long long dis[MAXN];
struct Edge{
	int y,c;
	Edge *next;
}pool[MAXM * 2],*first[MAXN],*mem;

inline void addedge(int x,int y,int c){
	mem->y = y; mem->next = first[x]; mem->c = c; first[x] = mem ++;
	mem->y = x; mem->next = first[y]; mem->c = c; first[y] = mem ++;
}
long long SPFA(){
	int head = 0,tail = 0,now;
	for(int i = 0;i < n;++ i) dis[i] = oo,in[i] = 0;;
	q[tail ++] = S; dis[S] = 0; in[S] = 1;
	while(head < tail){
		now = q[head ++]; in[now] = false;
		for(Edge *j = first[now];j;j = j->next)
		if(v[j->y] && dis[now] + j->c < dis[j->y]){
			dis[j->y] = dis[now] + j->c;
			if(!in[j->y]){
				in[j->y] = true;
				q[tail ++] = j->y;
			}
		}
	}
	return dis[T];
}
int main(){
	while(scanf("%d%d",&n,&m) != EOF && n + m){
		mem = pool;
		for(int i = 0;i < n;++ i) first[i] = 0,v[i] = true;
		for(int x,y,c,i = 0;i < m;++ i){
			scanf("%d%d%d",&x,&y,&c);
			addedge(x - 1,y - 1,c);
		}
		S = 0; T = n - 1;
		long long ret = 0LL;
		for(int i = 1;i < n - 1;++ i){
			v[i] = false;
			long long tmp = SPFA();
			if(tmp > ret) ret = tmp;
			v[i] = true;
		}
		if(ret < oo) printf("%I64d\n",ret);
		else puts("Inf");
	}
	return 0;
}
