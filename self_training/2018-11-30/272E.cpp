#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e4 + 1, maxm = (int)2e4 + 1, maxs = maxn * 784 + 1;
int n, m, pos[maxm], etot, qtot, stot, val[maxm];
struct Segment {
	int lch, rch, tim0, tim1;
} seg[maxs];
vector<int> eids[maxm << 1 | 1];
struct Event {
	int sta, end, typ, L, R;
} e[maxm];
struct Query {
	int L, R;
} que[maxm];
inline int getIdx(int L, int R) {
	return (L + R) | (L < R);
}
void addEvent(int L, int R, int l, int r, int id) {
	if(l <= L && R <= r) {
		eids[getIdx(L, R)].push_back(id);
	} else {
		int M = (L + R) >> 1;
		if(l <= M)
			addEvent(L, M, l, r, id);
		if(r > M)
			addEvent(M + 1, R, l, r, id);
	}
}
int segInit(char *buf, int L, int R) {
	int rt = ++stot;
	seg[rt].tim0 = seg[rt].tim1 = -1;
	if(L == R) {
		(buf[L] == '0' ? seg[rt].tim0 : seg[rt].tim1) = 0;
	} else {
		int M = (L + R) >> 1;
		seg[rt].lch = segInit(buf, L, M);
		seg[rt].rch = segInit(buf, M + 1, R);
	}
	return rt;
}
int segUpd(int rt, int L, int R, int l, int r, int typ, int tim) {
	int tr = rt;
	rt = ++stot;
	seg[rt] = seg[tr];
	if(l <= L && R <= r) {
		int &cur = typ == 0 ? seg[rt].tim0 : seg[rt].tim1;
		if(cur < tim)
			cur = tim;
	} else {
		int M = (L + R) >> 1;
		if(l <= M)
			seg[rt].lch = segUpd(seg[rt].lch, L, M, l, r, typ, tim);
		if(r > M)
			seg[rt].rch = segUpd(seg[rt].rch, M + 1, R, l, r, typ, tim);
	}
	return rt;
}
int segDfs(int rt, int L, int R, int l, int r, int t0 = -1, int t1 = -1) {
	if(t0 < seg[rt].tim0)
		t0 = seg[rt].tim0;
	if(t1 < seg[rt].tim1)
		t1 = seg[rt].tim1;
	if(L == R)
		return t0 < t1;
	int M = (L + R) >> 1;
	if(r <= M)
		return segDfs(seg[rt].lch, L, M, l, r, t0, t1);
	if(l > M)
		return segDfs(seg[rt].rch, M + 1, R, l, r, t0, t1);
	return segDfs(seg[rt].lch, L, M, l, r, t0, t1) + segDfs(seg[rt].rch, M + 1, R, l, r, t0, t1);
}
void solve(int rt, int L, int R) {
	vector<int> &cur = eids[getIdx(L, R)];
	for(vector<int>::iterator it = cur.begin(); it != cur.end(); ++it) {
		Event &curE = e[*it];
		rt = segUpd(rt, 1, n, curE.L, curE.R, curE.typ, curE.sta);
	}
	if(L == R) {
		val[L] = segDfs(rt, 1, n, que[L].L, que[L].R);
	} else {
		int M = (L + R) >> 1;
		solve(rt, L, M);
		solve(rt, M + 1, R);
	}
}
int main() {
	static char buf[maxn];
	scanf("%d%d%s", &n, &m, buf);
	int rt = segInit(buf - 1, 1, n);
	for(int i = 1; i <= m; ++i) {
		int typ, u, v;
		scanf("%d", &typ);
		if(typ == 1 || typ == 2) {
			scanf("%d%d", &u, &v);
			pos[i] = ++etot;
			e[etot] = (Event){i, m, typ - 1, u, v};
		} else if(typ == 3) {
			scanf("%d", &u);
			e[pos[u]].end = min(e[pos[u]].end, i);
		} else {
			scanf("%d%d", &u, &v);
			que[++qtot] = (Query){u, v};
			val[qtot] = i;
		}
	}
	for(int i = 1; i <= etot; ++i) {
		int pL = lower_bound(val + 1, val + qtot + 1, e[i].sta) - val;
		int pR = upper_bound(val + 1, val + qtot + 1, e[i].end) - val - 1;
		if(1 <= pL && pL <= pR && pR <= qtot)
			addEvent(1, qtot, pL, pR, i);
	}
	if(qtot)
		solve(rt, 1, qtot);
	for(int i = 1; i <= qtot; ++i)
		printf("%d\n", val[i]);
	return 0;
}
