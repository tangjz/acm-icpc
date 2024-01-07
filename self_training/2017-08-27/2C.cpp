#include <cstdio>
#include <vector>
#include <algorithm>
const int maxn = 100001, maxd = 17;
int len, mod, dt, a[maxn], sa[maxn], rk[maxn], ht[maxn], st[maxn][maxd], Log[maxn];
int m, f[maxn], g[maxn], c[maxn], ans[maxn];
std::vector<int> idx[maxn];
int lcp(int L, int R) {
	if(L == R) return maxn;
	int k = Log[R - (L++)];
	return std::min(st[L][k], st[R - (1 << k) + 1][k]);
}
void suffix_array() {
	int *x = f, *y = g; m = mod;
	for(int i = 0; i < m; ++i) c[i] = 0;
	for(int i = 0; i < len; ++i) ++c[x[i] = a[i]];
	for(int i = 1; i < m; ++i) c[i] += c[i - 1];
	for(int i = len - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for(int k = 1, p = 0; k <= len; k <<= 1, m = p, p = 0) {
		for(int i = len - k; i < len; ++i) y[p++] = i;
		for(int i = 0; i < len; ++i)
			if(sa[i] >= k) y[p++] = sa[i] - k;
		for(int i = 0; i < m; ++i) c[i] = 0;
		for(int i = 0; i < len; ++i) ++c[x[y[i]]];
		for(int i = 0; i < m; ++i) c[i] += c[i - 1];
		for(int i = len - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		std::swap(x, y), p = 1, x[sa[0]] = 0;
		for(int i = 1; i < len; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] 
			&& y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
		if(p >= len) break;
	}
	for(int i = 0; i < len; ++i) rk[sa[i]] = i;
	for(int i = 0, j, k = 0; i < len; ++i) {
		if(k) --k;
		if(!rk[i]) continue;
		for(j = sa[rk[i] - 1]; a[i + k] == a[j + k]; ++k);
		ht[rk[i]] = k;
	}
	for(int i = 2; i <= len; ++i) Log[i] = Log[i >> 1] + 1;
	for(int i = 0; i < len; ++i) st[i][0] = ht[i];
	for(int d = 1; 1 << d <= len; ++d)
		for(int i = 0; i + (1 << (d - 1)) < len; ++i)
			st[i][d] = std::min(st[i][d - 1], st[i + (1 << (d - 1))][d - 1]);
}
bool cmp(int u, int v, int add) {
	int com = rk[u] < rk[v] ? lcp(rk[u], rk[v]) : lcp(rk[v], rk[u]);
	return com < len && (a[(u + com) % len] + add) % mod < (a[(v + com) % len] + add) % mod;
}
int main() {
	scanf("%d%d%d", &len, &mod, &dt);
	for(int i = 0; i < len; ++i) {
		scanf("%d", a + i);
		idx[a[i]].push_back(i);
	}
	for(int i = 0; i < len; ++i)
		a[len + i] = a[i];
	len <<= 1;
	suffix_array();
	len >>= 1;
	for(int i = 0; i < mod; ++i)
		ans[i] = -1;
	for(int i = 0; i < mod; ++i) {
		if(!idx[i].size())
			continue;
		int add = i ? mod - i : 0, low = idx[i][0];
		for(int j = 1, sz = (int)idx[i].size(); j < sz; ++j)
			if(cmp(idx[i][j], low, add))
				low = idx[i][j];
		ans[add] = a[(low + dt - 1) % len];
	}
	for(int i = 1; i < mod; ++i)
		if(ans[i] == -1)
			ans[i] = ans[i - 1];
	if(ans[0] == -1)
		ans[0] = ans[mod - 1];
	for(int i = 1; i < mod; ++i)
		if(ans[i] == -1)
			ans[i] = ans[i - 1];
	for(int i = 0; i < mod; ++i)
		printf("%d\n", (ans[i] + i) % mod);
	return 0;
}
