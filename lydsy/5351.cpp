#include <bits/stdc++.h>
using namespace std;
const int maxs = (int)2e5 + 1, maxd = 18;
int dt, len, sa[maxs], rk[maxs], Log[maxs], st[maxd][maxs], *ht = st[0];
int buf[maxs];
inline int lcp(int u, int v) {
	u = rk[u];
	v = rk[v];
	if(u > v)
		swap(u, v);
	if(u == v)
		return maxs;
	int d = Log[v - (u++)];
	return min(st[d][u], st[d][v - (1 << d) + 1]);
}
int main() {
	int n, m;
	static int que[maxs];
	scanf("%d%d", &n, &dt);
	for(int i = 0; i < n; ++i)
		scanf("%d", buf + i);
	memcpy(que, buf, n * sizeof(int));
	sort(que, que + n);
	m = unique(que, que + n) - que;
	for(int i = 0; i < n; ++i)
		buf[i] = lower_bound(que, que + m, buf[i]) - que + 1;
	len = n;
	buf[len++] = ++m;
	for(int i = n - 1; i >= 0; --i)
		buf[len++] = buf[i];
	buf[len] = 0;
	int *x = rk, *y = ht, *c = Log;
	memset(c, 0, (++m) * sizeof(int));
	for(int i = 0; i < len; ++i)
		++c[x[i] = buf[i]];
	for(int i = 1; i < m; ++i)
		c[i] += c[i - 1];
	for(int i = len - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for(int j = 0, k = 1; k < len; k <<= 1, m = j, j = 0) {
		for(int i = len - k; i < len; ++i)
			y[j++] = i;
		for(int i = 0; i < len; ++i)
			if(sa[i] >= k)
				y[j++] = sa[i] - k;
		memset(c, 0, m * sizeof(int));
		for(int i = 0; i < len; ++i)
			++c[x[y[i]]];
		for(int i = 1; i < m; ++i)
			c[i] += c[i - 1];
		for(int i = len - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		j = 1;
		x[sa[0]] = 0;
		for(int i = 1; i < len; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? j - 1 : j++;
		x[len] = j;
		if(j >= len)
			break;
	}
	ht[0] = Log[0] = Log[1] = 0;
	for(int i = 0; i < len; ++i)
		rk[sa[i]] = i;
	for(int i = 0, j, k = 0; i < len; ++i) {
		k && (--k);
		if(!rk[i])
			continue;
		for(j = sa[rk[i] - 1]; buf[i + k] == buf[j + k]; ++k);
		ht[rk[i]] = k;
	}
	for(int i = 2; i <= len; ++i) 
		Log[i] = Log[i >> 1] + 1;
	for(int i = 1; 1 << i <= len; ++i)
		for(int j = 0; j + (1 << (i - 1)) < len; ++j)
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
	long long ans = 0;
	for(int i = 1; i + dt + i <= n; ++i)
		for(int x = 0, y = dt + i; y < n; x += i, y += i) {
			int lft = min(lcp(2 * n - x, 2 * n - y), i), rht = min(lcp(x, y), i);
			ans += max(lft + rht - i, 0);
		}
	printf("%lld\n", ans);
	return 0;
}