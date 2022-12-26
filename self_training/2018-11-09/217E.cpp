#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = 21;
int n, m, q;
LL val[maxn], seg[maxn << 1 | 1][maxm], res[maxm];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_init(int L, int R) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt][L % m] = val[L] - val[L - 1];
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_init(L, M);
	seg_init(M + 1, R);
	for(int i = 0; i < m; ++i)
		seg[rt][i] = seg[lch][i] + seg[rch][i];
}
void seg_upd(int L, int R, int x) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt][L % m] = val[L] - val[L - 1];
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		seg_upd(L, M, x);
	if(x + 1 > M)
		seg_upd(M + 1, R, x);
	for(int i = 0; i < m; ++i)
		seg[rt][i] = seg[lch][i] + seg[rch][i];
}
void seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r) {
		int rt = seg_idx(L, R);
		for(int i = 0; i < m; ++i)
			res[i] += seg[rt][i];
		return;
	}
	int M = (L + R) >> 1;
	if(l <= M)
		seg_que(L, M, l, r);
	if(r > M)
		seg_que(M + 1, R, l, r);
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%lld", val + i);
	seg_init(1, n);
	while(q--) {
		int typ;
		scanf("%d", &typ);
		if(typ == 1) {
			int l, r;
			scanf("%d%d", &l, &r);
			if(r - l + 1 < m) {
				int ans = 0;
				for(int i = l; i <= r; ++i)
					ans += val[i] != 0;
				printf("%d\n", ans);
				continue;
			}
			for(int i = 0; i < m; ++i)
				res[i] = 0;
			if(l < r)
				seg_que(1, n, l + 1, r);
			res[l % m] += val[l];
			res[(r + 1) % m] -= val[r];
			int ans = 0;
			map<LL, int> ctr;
			for(int i = 0; i < m; ++i) {
				res[i] += i ? res[i - 1] : 0;
				ans = max(ans, ++ctr[res[i]]);
			}
			printf("%d\n", m - ans);
		} else {
			int x;
			scanf("%d", &x);
			scanf("%lld", val + x);
			seg_upd(1, n, x);
		}
	}
	return 0;
}