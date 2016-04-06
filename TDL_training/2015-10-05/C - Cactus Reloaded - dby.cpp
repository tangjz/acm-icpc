#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 50005,MAXE = 3030303;
int dis[MAXN],low[MAXN],q[MAXN],loop[MAXN],dfn[MAXN],n,top,sig,ans,m;

struct Edge{
	int y;
	Edge *next;
}pool[MAXE],*mem,*first[MAXN],*stk[MAXE];
inline void addedge(int a,int b){
	mem->y = b; mem->next = first[a]; first[a] = mem ++;
	mem->y = a; mem->next = first[b]; first[b] = mem ++;
}
inline int min(int a,int b){return a < b ? a : b;}
inline int max(int a,int b){return a > b ? a : b;}

void calc(int tot,int mid){
	int head = 0,tail = 0;
	q[tail ++] = 0;
	for(int i = 1;i < tot;++ i){
		while(head < tail && i - q[head] > mid) ++ head;
		ans = max(ans,dis[loop[q[head]]] + dis[loop[i]] + i - q[head]);
		/*
		printf("%d %d : %d\n",loop[i],loop[q[head]],ans);
		*/
		while(tail > head && dis[loop[q[tail - 1]]] - q[tail - 1] < dis[loop[i]] - i) -- tail;
		q[tail ++] = i;
	}
}
void dfs(int cur,int fa){
	dfn[cur] = low[cur] = ++ sig; dis[cur] = 0;
	int sec = 0;
	for(Edge *j = first[cur];j;j = j->next)
	if(j->y != fa){
		if(dfn[j->y]) low[cur] = min(low[cur],dfn[j->y]);
		else{
			stk[++ top] = j;
			dfs(j->y,cur); low[cur] = min(low[cur],low[j->y]);	
			if(low[j->y] > dfn[cur]){
				-- top;
				int tmp = dis[j->y] + 1;
				if(tmp > dis[cur]) sec = dis[cur],dis[cur] = tmp;
				else if(tmp > sec) sec = tmp;
			}else if(low[j->y] == dfn[cur]){
				int cnt = 0;
				do{
					loop[cnt ++] = stk[top]->y;
				}while(stk[top --] != j);
				loop[cnt ++] = cur;
				int lopdis = 0;
				for(int i = 0;i < cnt;++ i){
					loop[cnt + i] = loop[i];
					if(loop[i] != cur && dis[loop[i]] + min(cnt - 1 - i,i + 1) > lopdis)
						lopdis = dis[loop[i]] + min(cnt - 1 - i,i + 1);
				}
				calc(cnt << 1,cnt >> 1);
				if(lopdis > dis[cur]) sec = dis[cur],dis[cur] = lopdis;
				else if(lopdis > sec) sec = lopdis;
				/*
				printf("lopdis %d = %d\n",cur,lopdis);
				*/
			}
		}
	}
	ans = max(ans,sec + dis[cur]);
	/*
	printf("%d : %d %d %d\n",cur,ans,sec,dis[cur]);
	*/
}

int main(){
	while(scanf("%d%d",&n,&m) != EOF){
		mem = pool;
		for(int i = 1;i <= n;++ i) first[i] = 0,dfn[i] = 0,low[i] = 0;
		for(int k,i = 0,x,y;i < m;++ i){
			scanf("%d",&k);
			scanf("%d",&x);
			for(int j = 1;j < k;++ j){
				scanf("%d",&y);
				addedge(x,y); x = y;
			}
		}
		sig = 0; ans = 0; top = 0;
		dfs(1,0);
		/*
		for(int i = 1;i <= n;++ i) printf("%d : %d %d\n",i,dfn[i],low[i]);
		*/
		printf("%d\n",ans);
	}
	return 0;
}
