#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxm = maxn << 3 | 1;
int n, m, a[maxn], pL[maxn], pR[maxn], etot, ord[maxm], que[maxm];
long long ans[maxn];
struct Event {
	int typ, x, y, v;
} eve[maxm];
bool cmp(int const &u, int const &v) {
	if(eve[u].x != eve[v].x)
		return eve[u].x < eve[v].x;
	return eve[u].typ < eve[v].typ;
}
void addEvent(int typ, int x, int y, int v) {
	if(x < 0 || x > n || y < 0 || y > n || !v)
		return;
	ord[etot] = etot;
	eve[etot++] = (Event){typ, x, y, v};
}
void solve(int L, int R) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	solve(L, M);
	solve(M + 1, R);
	__int128 cnt[9] = {};
	for(int i = L, j = M + 1, k = 0; i <= M || j <= R; ) {
		int u = ord[i], v = ord[j];
		if(j > R || (i <= M && eve[u].y <= eve[v].y)) {
			if(!eve[u].typ) {
				__int128 v0 = eve[u].v;		cnt[0] += v0;
				__int128 v1 = v0 * eve[u].x;	cnt[1] += v1;
				__int128 v2 = v0 * eve[u].y;	cnt[2] += v2;
				__int128 v3 = v1 * eve[u].x;	cnt[3] += v3;
				__int128 v4 = v2 * eve[u].y;	cnt[4] += v4;
				__int128 v5 = v1 * eve[u].y;	cnt[5] += v5;
				__int128 v6 = v5 * eve[u].x;	cnt[6] += v6;
				__int128 v7 = v5 * eve[u].y;	cnt[7] += v7;
			}
			que[k++] = ord[i++];
		} else {
			if(eve[v].typ) {
				__int128 v7 = 1;
				__int128 v6 = -1;
				__int128 v5 = 2;
				__int128 v4 = -eve[v].x - 1;
				__int128 v3 = eve[v].y + 1;
				__int128 v2 = v4 * (-eve[v].x + 1);
				__int128 v1 = v3 * (-eve[v].y - 3);
				__int128 v0 = v3 * (eve[v].x + 1) * (eve[v].y - eve[v].x + 2);
				ans[eve[v].typ] += eve[v].v * (cnt[0] * v0 + cnt[1] * v1 + cnt[2] * v2 + cnt[3] * v3 + cnt[4] * v4 + cnt[5] * v5 + cnt[6] * v6 + cnt[7] * v7) / 2;
			}
			que[k++] = ord[j++];
		}
	}
	memcpy(ord + L, que, (R - L + 1) * sizeof(int));
}
int main() {
	static int stk[maxn];
	scanf("%d%d", &n, &m);
	for(int i = 1, sz = 0; i <= n; ++i) {
		scanf("%d", a + i);
		for( ; sz && a[stk[sz - 1]] < a[i]; --sz);
		pL[i] = (sz ? stk[sz - 1] : 0) + 1;
		stk[sz++] = i;
	}
	for(int i = n, sz = 0; i >= 1; --i) {
		for( ; sz && a[stk[sz - 1]] <= a[i]; --sz);
		pR[i] = (sz ? stk[sz - 1] : n + 1) - 1;
		stk[sz++] = i;
		addEvent(0, pL[i], i, a[i]);
		addEvent(0, pL[i], pR[i] + 1, -a[i]);
		addEvent(0, i + 1, i, -a[i]);
		addEvent(0, i + 1, pR[i] + 1, a[i]);
	}
	for(int i = 1; i <= m; ++i) {
		int xL, xR, yL, yR;
		scanf("%d%d%d%d", &xL, &xR, &yL, &yR);
		addEvent(i, xR, yR, 1);
		addEvent(i, xL - 1, yR, -1);
		addEvent(i, xR, yL - 1, -1);
		addEvent(i, xL - 1, yL - 1, 1);
	}
	sort(ord, ord + etot, cmp);
	if(etot)
		solve(0, etot - 1);
	for(int i = 1; i <= m; ++i)
		printf("%llu\n", ans[i]);
	return 0;
}
