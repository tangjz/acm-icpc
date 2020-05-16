#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1, maxd = 18, INF = 0x3f3f3f3f;
int n, sa[maxn], rk[maxn], Log[maxn], st[maxd | 1][maxn], *ht = st[0];
char buf[maxn];
void SuffixArray() {
	int i, j, k, *x = rk, *y = ht, *c = Log, m = 256;
	memset(c, 0, m * sizeof(int));
	for(i = 0; i < n; ++i) ++c[x[i] = buf[i]];
	for(i = 1; i < m; ++i) c[i] += c[i - 1];
	for(i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for(k = 1; k <= n; k <<= 1, m = j) {
		for(i = n - k, j = 0; i < n; ++i) y[j++] = i;
		for(i = 0; i < n; ++i) if(sa[i] >= k) y[j++] = sa[i] - k;
		memset(c, 0, m * sizeof(int));
		for(i = 0; i < n; ++i) ++c[x[y[i]]];
		for(i = 0; i < m; ++i) c[i] += c[i - 1];
		for(i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
		for(swap(x, y), i = 1, j = 1, x[sa[0]] = 0; i < n; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? j - 1 : j++;
		x[n] = j;
		if(j >= n) break;
	}
	for(i = 0; i < n; ++i) rk[sa[i]] = i;
	for(i = k = ht[0] = 0; i < n; ++i) {
		if(k) --k;
		if(!rk[i]) continue;
		for(j = sa[rk[i] - 1]; buf[i + k] == buf[j + k]; ++k);
		ht[rk[i]] = k;
	}
	for(i = 1, Log[0] = -1; i < n; ++i)
		Log[i] = Log[i >> 1] + 1;
	for(i = 1; i <= Log[n - 1]; ++i)
		for(j = 1; j + (1 << i) <= n; ++j)
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
inline int lcp(int L, int R) {
	int d = Log[R - (L++)];
	return min(st[d][L], st[d][R - (1 << d) + 1]);
}
inline pair<int, int> getRange(int x, int len) {
	int L, R, P;
	for(L = 0, R = x; L < R; ) {
		int M = (L + R) >> 1;
		if(lcp(M, x) < len) {
			L = M + 1;
		} else {
			R = M;
		}
	}
	for(P = L, L = x, R = n - 1; L < R; ) {
		int M = (L + R + 1) >> 1;
		if(lcp(x, M) < len) {
			R = M - 1;
		} else {
			L = M;
		}
	}
	return make_pair(P, L);
}
pair<int, int> seg[maxn << 1 | 1];
int seg2[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int l, int r, pair<int, int> v) {
	if(l <= L && R <= r) {
		int rt = seg_idx(L, R);
		seg[rt] = max(seg[rt], v);
	} else {
		int M = (L + R) >> 1;
		if(l <= M)
			seg_upd(L, M, l, r, v);
		if(r > M)
			seg_upd(M + 1, R, l, r, v);
	}
}
pair<int, int> seg_que(int L, int R, int x) {
	pair<int, int> ret = make_pair(0, 0);
	while(L < R) {
		ret = max(ret, seg[seg_idx(L, R)]);
		int M = (L + R) >> 1;
		if(x <= M) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	return max(ret, seg[seg_idx(L, R)]);
}
void seg2_upd(int L, int R, int x, int v) {
	while(L < R) {
		int rt = seg_idx(L, R);
		seg2[rt] = min(seg2[rt], v);
		int M = (L + R) >> 1;
		if(x <= M) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	int rt = seg_idx(L, R);
	seg2[rt] = min(seg2[rt], v);
}
int seg2_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg2[seg_idx(L, R)];
	int M = (L + R) >> 1, ret = INF;
	if(l <= M)
		ret = min(ret, seg2_que(L, M, l, r));
	if(r > M)
		ret = min(ret, seg2_que(M + 1, R, l, r));
	return ret;
}
int main() {
	scanf("%d%s", &n, buf);
	SuffixArray();
	int ans = 0;
	memset(seg2, 0x3f, (n << 1) * sizeof(int));
	for(int i = n - 1; i >= 0; --i) {
		pair<int, int> tmp = seg_que(0, n - 1, rk[i]);
		if(tmp.second) {
			pair<int, int> rng = getRange(rk[i], -tmp.second);
			++tmp.first;
			tmp.second -= seg2_que(0, n - 1, rng.first, rng.second) - i;
		} else {
			tmp = make_pair(1, -1);
		}
		ans = max(ans, tmp.first);
		pair<int, int> rng = getRange(rk[i], -tmp.second);
		seg_upd(0, n - 1, rng.first, rng.second, tmp);
		seg2_upd(0, n - 1, rk[i], i);
	}
	printf("%d\n", ans);
	return 0;
}
