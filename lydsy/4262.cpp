#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = maxn << 4 | 1;
int m, low, upp, etot, ord[maxm], que[maxm];
LL ans[maxn];
struct Event {
	int typ, x, y;
	LL v;
} eve[maxm];
bool cmp(int const &u, int const &v) {
	if(eve[u].x != eve[v].x)
		return eve[u].x < eve[v].x;
	if(eve[u].y != eve[v].y)
		return eve[u].y < eve[v].y;
	return eve[u].typ < eve[v].typ;
}
void addEvent(int typ, int x, int y, int v) {
	if(x < low || x > upp || y < low || y > upp || !v)
		return;
	ord[etot] = etot;
	eve[etot++] = (Event){typ, x, y, (LL)v};
}
void solve(int L, int R) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	solve(L, M);
	solve(M + 1, R);
	LL cnt[5] = {};
	for(int i = L, j = M + 1, k = 0; i <= M || j <= R; ) {
		int u = ord[i], v = ord[j];
		if(j > R || (i <= M && eve[u].y <= eve[v].y)) {
			if(!eve[u].typ) {
				LL v0 = eve[u].v, v1 = v0 * eve[u].x, v2 = v0 * eve[u].y, v3 = v1 * eve[u].y;
				cnt[0] += v0;
				cnt[1] += v1;
				cnt[2] += v2;
				cnt[3] += v3;
			}
			que[k++] = ord[i++];
		} else {
			if(eve[v].typ) {
				LL v3 = 1;
				LL v2 = -eve[v].x - 1;
				LL v1 = -eve[v].y - 1;
				LL v0 = v2 * v1;
				ans[eve[v].typ] += eve[v].v * (cnt[0] * v0 + cnt[1] * v1 + cnt[2] * v2 + cnt[3] * v3);
			}
			que[k++] = ord[j++];
		}
	}
	memcpy(ord + L, que, (R - L + 1) * sizeof(int));
}
void solve() {
	sort(ord, ord + etot, cmp);
	int tot = 0;
	for(int i = 0; i < etot; ) {
		int typ = eve[ord[i]].typ, x = eve[ord[i]].x, y = eve[ord[i]].y;
		LL v = 0;
		for( ; i < etot && eve[ord[i]].typ == typ && eve[ord[i]].x == x && eve[ord[i]].y == y; ++i)
			v += eve[ord[i]].v;
		if(v)
			eve[ord[tot++]] = (Event){typ, x, y, v};
	}
	if(tot)
		solve(0, tot - 1);
}
int main() {
	static int seq[4][maxn], *a = seq[0], *pL = seq[1], *pR = seq[2], *stk = seq[3];
	scanf("%d", &m);
	low = maxn;
	upp = 0;
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d%d%d", seq[0] + i, seq[1] + i, seq[2] + i, seq[3] + i);
		low = min(low, min(seq[0][i], seq[2][i]));
		upp = max(upp, max(seq[1][i], seq[3][i]));
	}
	for(int i = 1; i <= m; ++i) {
		int &xL = seq[0][i], &xR = seq[1][i], &yL = seq[2][i], &yR = seq[3][i];
		addEvent(i, xR, yR, 1);
		addEvent(i, xL - 1, yR, -1);
		addEvent(i, xR, yL - 1, -1);
		addEvent(i, xL - 1, yL - 1, 1);
	}
	for(int i = 1, u = 1, v = 1, p = (int)1e9; i <= upp; ++i) {
		u = (((LL)u << 10) - u) % p;
		v = (((LL)v << 10) + v) % p;
		a[i] = u ^ v;
	}
	for(int i = low, sz = 0; i <= upp; ++i) {
		for( ; sz && a[stk[sz - 1]] < a[i]; --sz);
		pL[i] = sz ? stk[sz - 1] + 1 : low;
		stk[sz++] = i;
	}
	for(int i = upp, sz = 0; i >= low; --i) {
		for( ; sz && a[stk[sz - 1]] <= a[i]; --sz);
		pR[i] = sz ? stk[sz - 1] - 1 : upp;
		stk[sz++] = i;
		addEvent(0, pL[i], i, a[i]);
		addEvent(0, pL[i], pR[i] + 1, -a[i]);
		addEvent(0, i + 1, i, -a[i]);
		addEvent(0, i + 1, pR[i] + 1, a[i]);
	}
	for(int i = low, sz = 0; i <= upp; ++i) {
		for( ; sz && a[stk[sz - 1]] > a[i]; --sz);
		pL[i] = sz ? stk[sz - 1] + 1 : low;
		stk[sz++] = i;
	}
	for(int i = upp, sz = 0; i >= low; --i) {
		for( ; sz && a[stk[sz - 1]] >= a[i]; --sz);
		pR[i] = sz ? stk[sz - 1] - 1 : upp;
		stk[sz++] = i;
		addEvent(0, pL[i], i, -a[i]);
		addEvent(0, pL[i], pR[i] + 1, a[i]);
		addEvent(0, i + 1, i, a[i]);
		addEvent(0, i + 1, pR[i] + 1, -a[i]);
	}
	solve();
	for(int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
