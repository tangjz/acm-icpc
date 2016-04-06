#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstdlib>
using namespace std;
#define lson l,mid,root << 1
#define rson mid + 1,r,root << 1 | 1
const int MAXN = 10003,MAXM = 102,oo = ~0U>>2;
int val[MAXN],c[MAXN << 1],s[MAXN << 1],l[MAXN << 1],r[MAXN << 1],ord[MAXN << 1],n,m;

inline int min(int x,int y){return x < y ? x : y;}
inline bool cmp(int x,int y){
	return l[x] < l[y];
}
struct Tree{
	int tag[MAXN << 2];
	void build(int l,int r,int root){
		tag[root] = oo;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(lson); build(rson);
	}
	void modify(int L,int R,int x,int l,int r,int root){
		if(L <= l && R >= r){
			if(x < tag[root]) tag[root] = x;
			return;
		}
		int mid = (l + r) >> 1;
		if(L <= mid) modify(L,R,x,lson);
		if(R > mid) modify(L,R,x,rson);
	}
	int query(int p,int l,int r,int root){
		int ret = tag[root],tmp;
		if(l == r) return ret;
		int mid = (l + r)>> 1;
		if(p <= mid) tmp = query(p,lson);
		else tmp = query(p,rson);
		return min(ret,tmp);
	}
}tree[MAXM];

int main(){
	int cas = 0;
	while(scanf("%d%d",&n,&m) != EOF && (n != 0 || m != 0)){
		for(int i = 1;i < n;++ i) scanf("%d",&val[i + 1]);
		int tot = n + 1;
		val[1] = 0;
		val[0] = -1;
		for(int i = 0;i < n;++ i) scanf("%d",&c[i]);
		for(int i = 0,x;i < n;++ i){
			scanf("%d",&x);
			l[i] = lower_bound(val,val + tot,val[i + 1] - x) - val + 1;
			r[i] = upper_bound(val,val + tot,val[i + 1] + x) - val;
			s[i] = 1; ord[i] = i;
		}
		for(int i = 0;i < n;++ i){
			scanf("%d",&c[i + n]);
			l[i + n] = r[i + n] = i + 2;
			s[i + n] = 0; ord[i + n] = n + i;
		}
		sort(ord,ord + n + n,cmp);
		for(int i = 0;i <= m;++ i)
			tree[i].build(1,tot,1);
		tree[0].modify(1,1,0,1,tot,1);
		for(int i = 0;i < n + n;++ i){
			int nl = l[ord[i]],nr = r[ord[i]],nc = c[ord[i]],ns = s[ord[i]];
			for(int j = 0;j <= m - ns;++ j){
				int pre = tree[j].query(nl - 1,1,tot,1);
				if(pre != oo){
					pre += nc;
					tree[j + ns].modify(nl,nr,pre,1,tot,1);
				}
			}
		}
		int ret = oo;
		for(int tmp,i = 0;i <= m;++ i){
			tmp = tree[i].query(tot,1,tot,1);	
			if(tmp < ret) ret = tmp;
		}
		printf("Case %d: %d\n",++ cas,ret);
	}
}
