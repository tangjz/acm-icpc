#include <bits/stdc++.h>
using namespace std;
const int maxn = 201, maxs = (int)2e5 + 203, maxd = 19, INF = 0x3f3f3f3f;
int n, sta[maxn], slen[maxn], f[maxs];
int len, sa[maxs], rk[maxs], Log[maxs], st[maxd][maxs], *ht = st[0];
char buf[maxs];
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
int F(int idx, int pos) {
	int msk = sta[idx] + pos;
	if(f[msk] != -1)
		return f[msk];
	f[msk] = INF;
	int ret = 0, rem = slen[idx] - pos, adt = idx < n ? n : 0;
	for(int i = 0; i < n; ++i) {
		int tp = lcp(msk, sta[adt + i]);
		if(tp >= rem && tp >= slen[adt + i])
			return INF;
		if(tp >= rem) {
			ret = max(ret, rem + F(adt + i, rem));
		} else if(tp >= slen[adt + i]) {
			ret = max(ret, slen[adt + i] + F(idx, pos + slen[adt + i]));
		} else {
			ret = max(ret, tp);
		}
	}
	return f[msk] = min(ret, INF);
}

int main() {
	scanf("%d", &n);
	buf[len++] = '#';
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf + len);
		sta[i] = len;
		slen[i] = strlen(buf + len);
		len += slen[i];
		buf[len++] = '#';
	}
	for(int i = 0; i < n; ++i) {
		sta[n + i] = len;
		slen[n + i] = slen[i];
		for(int j = slen[i] - 1; j >= 0; --j)
			buf[len++] = buf[sta[i] + j];
		buf[len++] = '#';
	}
	int m = 256, *x = rk, *y = ht, *c = Log;
	memset(c, 0, m * sizeof(int));
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
	int ans = 0, tp;
	memset(f, -1, len * sizeof(int));
	for(int i = 0; i < n && ans < INF; ++i)
		for(int j = 0; j < slen[i] && ans < INF; ++j) {
			// even
			tp = lcp(sta[i] + j, sta[n + i] + slen[i] - j);
			if(tp >= slen[i] - j && tp >= j) {
				ans = INF;
			} else if(tp >= slen[i] - j) {
				ans = max(ans, 2 * (slen[i] - j + F(n + i, 2 * (slen[i] - j))));
			} else if(tp >= j) {
				ans = max(ans, 2 * (j + F(i, 2 * j)));
			} else {
				ans = max(ans, 2 * tp);
			}
			// odd
			tp = lcp(sta[i] + j, sta[n + i] + slen[i] - j - 1);
			if(tp >= slen[i] - j && tp >= j + 1) {
				ans = INF;
			} else if(tp >= slen[i] - j) {
				ans = max(ans, 2 * (slen[i] - j + F(n + i, 2 * (slen[i] - j) - 1)) - 1);
			} else if(tp >= j + 1) {
				ans = max(ans, 2 * (j + 1 + F(i, 2 * j + 1)) - 1);
			} else {
				ans = max(ans, 2 * tp - 1);
			}
		}
	if(ans < INF)
		printf("%d\n", ans);
	else
		puts("Infinity");
	return 0;
}
