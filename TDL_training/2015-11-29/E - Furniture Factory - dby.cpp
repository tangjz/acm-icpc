#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 830,MAXE = 103 * 503 * 10,oo = ~0U>>2;
int l[MAXN],r[MAXN],w[MAXN],n,m,S,T,q[MAXN],level[MAXN];

struct Edge{
	int y,cap;
	Edge *next,*op;
}pool[MAXE],*first[MAXN],*mem;
inline void addedge(int a,int b,int c){
	mem->y = b; mem->cap = c; mem->next = first[a]; first[a] = mem ++;
	mem->y = a; mem->cap = 0; mem->next = first[b]; first[b] = mem ++;
	first[a]->op = first[b]; first[b]->op = first[a];
}
bool build(){
	for(int i = S;i <= T;++ i) level[i] = -1;
	int head = 0,tail = 0,now;
	q[tail ++] = S; level[S] = 0;
	for(now = S;head < tail;now = q[++ head])
		for(Edge *j = first[now];j;j = j->next)
		if(j->cap > 0 && level[j->y] == -1)
			level[q[tail ++] = j->y] = level[now] + 1;
	return level[T] != -1;
}
int aug(int cur,int m){
	if(cur == T) return m;
	int l = m,tmp;
	for(Edge *j = first[cur];j && l;j = j->next)
	if(j->cap > 0 && level[j->y] == level[cur] + 1){
		tmp = (l > j->cap) ? j->cap : l;
		tmp = aug(j->y,tmp);
		j->cap -= tmp; j->op->cap += tmp; l -= tmp;
		if(l == 0) break;
	}
	if(l == m) level[cur] = -1;
	return m - l;
}

void print(){
	for(int i = 1;i <= n;++ i){
		int tot = 0,last = -1;
		for(Edge *j = first[i];j && j->y > n;j = j->next)
		if(j->cap == 0){
			int e = j->y - n;
			if(e == last + 1) r[tot - 1] = e;
			else{
				l[tot] = r[tot] = e; ++ tot;
			}
			last = e;
		}
		printf("%d",tot);
		for(int j = 0;j < tot;++ j) printf(" %d %d",l[j],r[j] + 1);
		puts("");
	}
}

int main(){
	int TT;
	scanf("%d",&TT);
	while(TT --){
		scanf("%d%d",&m,&n);
		T = S = 0;
		first[S] = 0;
		int std = 0;
		mem = pool;
		for(int i = 1;i <= n;++ i){
			first[i] = 0;
			scanf("%d%d%d",&l[i],&w[i],&r[i]);
			if(r[i] > T) T = r[i];
			addedge(S,i,w[i]);
			std += w[i];
		}
		T += n + 1;
		for(int i = n + 1;i <= T;++ i) first[i] = 0;
		for(int i = 1;i <= n;++ i)
			for(int j = r[i] - 1;j >= l[i];-- j)
				addedge(i,n + j,1);
		for(int i = n + 1;i < T;++ i)
			addedge(i,T,m);

		int Maxflow = 0,dt;
		while(build())
			while((dt = aug(S,oo)))
				Maxflow += dt;

		if(Maxflow != std) puts("0");
		else print();
	}
	return 0;
}
