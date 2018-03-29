#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e4 + 3;
int n, m, sq, blk, perm[maxn], pos[maxn], mx, lft[maxn], rht[maxn], ans[maxn], tot;
pair<int *, int> stk[maxn << 2 | 1];
struct Query {
	int idx, L, R;
	bool operator < (Query const &t) const {
		if(pos[L] != pos[t.L])
			return pos[L] < pos[t.L];
		return R < t.R;
	}
} que[maxn];
inline void insert(int v) {
	int lv = lft[v - 1], rv = rht[v + 1], tp = lv + rv + 1;
	stk[++tot] = make_pair(lft + v, lft[v]);
	lft[v] = lv + 1;
	stk[++tot] = make_pair(rht + v, rht[v]);
	rht[v] = rv + 1;
	mx = max(mx, tp);
	if(lv) {
		stk[++tot] = make_pair(rht + v - lv, rht[v - lv]);
		rht[v - lv] = tp;
	}
	if(rv) {
		stk[++tot] = make_pair(lft + v + rv, lft[v + rv]);
		lft[v + rv] = tp;
	}
}
inline void rollback(int tim, int pmx) {
	for( ; tot > tim; --tot)
		*stk[tot].first = stk[tot].second;
	mx = pmx;
}
int main() {
	scanf("%d%d", &n, &m);
	for( ; sq * sq <= n; ++sq);
	blk = (n - 1) / --sq + 1;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", perm + i);
		pos[i] = pos[max(i - blk, 0)] + 1;
	}
	for(int i = 1; i <= m; ++i) {
		que[i].idx = i;
		scanf("%d%d", &que[i].L, &que[i].R);
	}
	sort(que + 1, que + m + 1);
	for(int i = 1; i <= m; ) {
		int pp = pos[que[i].L], qL = que[i].L, qR = qL;
		for( ; qL <= m && pos[qL] == pp; ++qL, ++qR);
		for( ; i <= m && pos[que[i].R] == pp; ++i) {
			for(int j = que[i].L; j <= que[i].R; ++j)
				insert(perm[j]);
			ans[que[i].idx] = mx;
			rollback(0, 0);
		}
		for( ; i <= m && pos[que[i].L] == pp; ++i) {
			for( ; qR <= que[i].R; ++qR)
				insert(perm[qR]);
			int tim = tot, pmx = mx, pL = qL;
			for( ; qL > que[i].L; --qL)
				insert(perm[qL - 1]);
			ans[que[i].idx] = mx;
			rollback(tim, pmx);
			qL = pL;
		}
		rollback(0, 0);
	}
	for(int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
