#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1, maxd = 18, maxc = 26;
char buf[maxn];
int n, sa[maxn], rk[maxn], ht[maxn];
void SuffixArray() {
	int m = 256, *x = rk, *y = ht;
	static int c[maxn];
	memset(c, 0, m * sizeof(int));
	for(int i = 0; i < n; ++i)
		++c[x[i] = buf[i]];
	x[n] = m;
	for(int i = 1; i < m; ++i)
		c[i] += c[i - 1];
	for(int i = n - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for(int dt = 1; dt <= n; dt <<= 1) {
		int tp = 0;
		for(int i = n - dt; i < n; ++i)
			y[tp++] = i;
		for(int i = 0; i < n; ++i)
			if(sa[i] >= dt)
				y[tp++] = sa[i] - dt;
		memset(c, 0, m * sizeof(int));
		for(int i = 0; i < n; ++i)
			++c[x[y[i]]];
		for(int i = 1; i < m; ++i)
			c[i] += c[i - 1];
		for(int i = n - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		x[sa[0]] = tp = 0;
		for(int i = 1; i < n; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + dt] == y[sa[i] + dt] ? tp : ++tp;
		m = x[n] = ++tp;
		if(m >= n)
			break;
	}
	for(int i = 0; i < n; ++i)
		rk[sa[i]] = i;
	for(int i = 0, dt = 0; i < n; ++i) {
		dt -= dt > 0;
		if(rk[i])
			for(int j = sa[rk[i] - 1]; buf[i + dt] == buf[j + dt]; ++dt);
		ht[rk[i]] = dt;
	}
}
int Log[maxn], st[maxd | 1][maxn];
int rk2[maxn], st2[maxd | 1][maxn];
inline int lcp(int L, int R) { // [L, R]
	if(L == n || R == n)
		return 0;
	if(L == R)
		return n - L;
	L = rk[L];
	R = rk[R];
	if(L > R)
		swap(L, R);
	int d = Log[R - (L++)];
	return min(st[d][L], st[d][R - (1 << d) + 1]);
}
inline int lcs(int L, int R) { // [L, R]
	if(L < 0 || R < 0)
		return 0;
	if(L == R)
		return L + 1;
	L = rk2[n - 1 - L];
	R = rk2[n - 1 - R];
	if(L > R)
		swap(L, R);
	int d = Log[R - (L++)];
	return min(st2[d][L], st2[d][R - (1 << d) + 1]);
}
int c[maxc | 1][maxn], pL[maxn], pR[maxn], st3[maxd | 1][maxn];
inline int rmq(int L, int R) {
	int d = Log[R - L + 1];
	return min(st3[d][L], st3[d][R - (1 << d) + 1]);
}
inline int solve(int L, int R) {
	int len = R - L + 1;
	if(len <= maxc) {
		bool chk = 0;
		for(int i = 0; i < maxc; ++i)
			if(c[i][R + 1] - c[i][L] > 1) {
				chk = 1;
				break;
			}
		if(!chk)
			return -1;
	}
	if(lcp(L, L + 1) >= len - 1)
		return 1;
	for(int i = 2; i * i <= len; ++i) {
		if(len % i > 0)
			continue;
		if(lcp(L, L + i) >= len - i)
			return 1;
		int j = len / i;
		if(i < j && lcp(L, L + j) >= len - j)
			return 1;
	}
	if(pR[L] <= R || pL[R] >= L)
		return 2;
	for(int i = 1, j; i * i <= n; ++i) {
		if(i + i <= len && lcp(L, L + len - i) >= i)
			return 2;
		j = rk[L] < i ? -1 : sa[rk[L] - i];
		if(L <= j && j <= R && (R - j + 1) * 2 <= len && lcp(L, j) >= R - j + 1)
			return 2;
		j = rk[L] + i < n ? sa[rk[L] + i] : -1;
		if(L <= j && j <= R && (R - j + 1) * 2 <= len && lcp(L, j) >= R - j + 1)
			return 2;
	}
	int o = buf[L] - 'a';
	if(c[o][R + 1] - c[o][L] > 1)
		return 3;
	o = buf[R] - 'a';
	if(c[o][R + 1] - c[o][L] > 1)
		return 3;
	return rmq(L, R) > R ? 4 : 3;
}
int dsuL[maxn], dsuR[maxn];
inline int dsuFind(int dsu[], int x) {
	return x == dsu[x] ? x : (dsu[x] = dsuFind(dsu, dsu[x]));
}
int main() {
	scanf("%d%s", &n, buf);
	Log[0] = -1;
	for(int i = 1; i <= n; ++i)
		Log[i] = Log[i >> 1] + 1;
	reverse(buf, buf + n);
	SuffixArray();
	memcpy(rk2, rk, n * sizeof(int));
	memcpy(st2[0], ht, n * sizeof(int));
	for(int d = 1; d <= Log[n - 1]; ++d)
		for(int i = 1; i + (1 << d) <= n; ++i)
			st2[d][i] = min(st2[d - 1][i], st2[d - 1][i + (1 << (d - 1))]);
	reverse(buf, buf + n);
	SuffixArray();
	memcpy(st[0], ht, n * sizeof(int));
	for(int d = 1; d <= Log[n - 1]; ++d)
		for(int i = 1; i + (1 << d) <= n; ++i)
			st[d][i] = min(st[d - 1][i], st[d - 1][i + (1 << (d - 1))]);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < maxc; ++j)
			c[j][i + 1] = c[j][i] + (buf[i] == 'a' + j);
		pL[i] = -1;
		pR[i] = n;
		dsuL[i] = dsuR[i] = i;
	}
	dsuL[n] = dsuR[n] = n;
	for(int per = 1; per + per <= n; ++per)
		for(int i = 0, j = per; j < n; i = j, j += per) {
			int L = i - lcs(i - 1, j - 1);
			int R = j + lcp(i, j); // [L, R)
			if(R - L < per + per)
				continue;
			for(int k = dsuFind(dsuL, L); k + per + per <= R; k = dsuFind(dsuL, k)) {
				pR[k] = k + per + per - 1;
				dsuL[k] = k + 1;
			}
			for(int k = dsuFind(dsuR, L + per + per - 1); k < R; k = dsuFind(dsuR, k)) {
				pL[k] = k - per - per + 1;
				dsuR[k] = k + 1;
			}
		}
	memcpy(st3[0], pR, n * sizeof(int));
	for(int d = 1; d <= Log[n]; ++d)
		for(int i = 0; i + (1 << d) <= n; ++i)
			st3[d][i] = min(st3[d - 1][i], st3[d - 1][i + (1 << (d - 1))]);
	int q;
	scanf("%d", &q);
	while(q--) {
		int L, R;
		scanf("%d%d", &L, &R);
		printf("%d\n", solve(--L, --R));
	}
	return 0;
}
