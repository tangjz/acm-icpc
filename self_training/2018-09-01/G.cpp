#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, INF = 0x3f3f3f3f;
int n, m, seg[maxn << 1 | 1], tot, f[maxn], g[maxn], cnt, pL[maxn], pR[maxn];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_build(int L, int R) {
	if(L == R) {
		scanf("%d", seg + seg_idx(L, R));
	} else {
		int M = (L + R) >> 1;
		seg_build(L, M);
		seg_build(M + 1, R);
		seg[seg_idx(L, R)] = min(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
	}
}
void seg_get(int L, int R, int l, int r) {
	if(l <= L && R <= r) {
		pL[cnt] = L;
		pR[cnt++] = R;
	} else {
		int M = (L + R) >> 1;
		if(l <= M)
			seg_get(L, M, l, r);
		if(M < r)
			seg_get(M + 1, R, l, r);
	}
}
int seg_find(int L, int R, int v) {
	while(L < R) {
		int M = (L + R) >> 1;
		if(seg[seg_idx(L, M)] <= v) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	return L;
}
void seg_upd(int L, int R, int x, int v) {
	if(L == R) {
		seg[seg_idx(L, R)] = v;
	} else {
		int M = (L + R) >> 1;
		if(x <= M)
			seg_upd(L, M, x, v);
		else
			seg_upd(M + 1, R, x, v);
		seg[seg_idx(L, R)] = min(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	seg_build(1, n);
	while(seg[seg_idx(1, n)] < INF) {
		int low = seg[seg_idx(1, n)];
		for( ; tot < maxn && g[tot] < low; ++tot) {
			f[tot + 1] = f[tot];
			g[tot + 1] = g[tot] + m;
		}
		if(tot == maxn)
			break;
		int cur = 1;
		while(seg[seg_idx(1, n)] <= g[tot]) {
			cnt = 0;
			seg_get(1, n, cur, n);
			if(cur > 1)
				seg_get(1, n, 1, cur - 1);
			for(int i = 0; i < cnt; ++i)
				if(seg[seg_idx(pL[i], pR[i])] <= g[tot]) {
					int x = seg_find(pL[i], pR[i], g[tot]);
					++f[tot];
					g[tot] -= seg[seg_idx(x, x)];
					seg_upd(1, n, x, INF);
				}
		}
	}
	scanf("%d", &m);
	while(m--) {
		int x;
		scanf("%d", &x);
		x = min(x, tot);
		printf("%d %d\n", f[x], g[x]);
	}
	return 0;
} 
