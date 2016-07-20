#include <set>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxm = 61, maxs = 10001, maxn = maxm * maxs, maxd = 20;
int m, n, pos[maxn], sz[maxn], sa[maxn], ht[maxn], rk[maxn], Log[maxn], st[maxd][maxn];
LL seg[maxn << 1];
char str[maxn], tmp[maxs];
std::set<LL> Hash;
inline int seg_idx(int L, int R)
{
	return L + R | L < R;
}
void seg_init(int L, int R)
{
	int rt = seg_idx(L, R);
	if(L == R)
	{
		seg[rt] = pos[sa[L]] == -1 ? 0 : 1LL << pos[sa[L]];
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_init(L, M);
	seg_init(M + 1, R);
	seg[rt] = seg[lch] | seg[rch];
}
LL seg_query(int L, int R, int l, int r)
{
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = L + R >> 1;
	if(r <= M)
		return seg_query(L, M, l, r);
	if(l > M)
		return seg_query(M + 1, R, l, r);
	return seg_query(L, M, l, r) | seg_query(M + 1, R, l, r);
}
void suffix_array()
{
	int *x = rk, *y = ht, *c = Log, tot;
	tot = 256;
	memset(c, 0, tot * sizeof(int));
	for(int i = 0; i < n; ++i)
		++c[x[i] = str[i]];
	for(int i = 1; i < tot; ++i)
		c[i] += c[i - 1];
	for(int i = n - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for(int k = 1; k < n; k <<= 1)
	{
		int p = 0;
		for(int i = n - k; i < n; ++i)
			y[p++] = i;
		for(int i = 0; i < n; ++i)
			if(sa[i] >= k)
				y[p++] = sa[i] - k;
		memset(c, 0, tot * sizeof(int));
		for(int i = 0; i < n; ++i)
			++c[x[y[i]]];
		for(int i = 1; i < tot; ++i)
			c[i] += c[i - 1];
		for(int i = n - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		std::swap(x, y);
		p = 1;
		x[sa[0]] = 0;
		for(int i = 1; i < n; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
		if(p >= n)
			break;
		tot = p;
	}
	for(int i = 0; i < n; ++i)
		rk[sa[i]] = i;
	for(int i = 0, j, k = 0; i < n; ++i)
	{
		if(k)
			--k;
		if(!rk[i])
		{
			ht[rk[i]] = 0;
			continue;
		}
		for(j = sa[rk[i] - 1]; str[i + k] == str[j + k]; ++k);
		ht[rk[i]] = k;
	}
	Log[1] = 0;
	for(int i = 2; i <= n; ++i)
		Log[i] = Log[i >> 1] + 1;
	for(int i = 0; i < n; ++i)
		st[0][i] = ht[i];
	for(int d = 1; d <= Log[n]; ++d)
		for(int i = 0; i + (1 << d - 1) < n; ++i)
			st[d][i] = std::min(st[d - 1][i], st[d - 1][i + (1 << d - 1)]);
}
int lcp(int L, int R)
{
	if(++L > R)
		return maxn;
	int d = Log[R - L + 1];
	return std::min(st[d][L], st[d][R - (1 << d) + 1]);
}
void check(int idx, int len)
{
	int L, R, M, pL, pR;
	L = 0, R = idx;
	while(L < R)
	{
		M = L + R >> 1;
		if(lcp(M, idx) < len)
			L = M + 1;
		else
			R = M;
	}
	pL = L;
	L = idx, R = n - 1;
	while(L < R)
	{
		M = L + R + 1 >> 1;
		if(lcp(idx, M) < len)
			R = M - 1;
		else
			L = M;
	}
	pR = L;
	Hash.insert(seg_query(0, n - 1, pL, pR));
}
int main()
{
	while(scanf("%d", &m) == 1 && m)
	{
		n = 0;
		for(int i = 0; i < m; ++i)
		{
			scanf("%s", tmp);
			int tlen = strlen(tmp);
			for(int j = 0; j < tlen; ++j)
			{
				pos[n] = i;
				sz[n] = tlen - j;
				str[n++] = tmp[j];
			}
			pos[n] = sz[n] = -1;
			str[n++] = i + 1;
		}
		str[n] = '\0';
		suffix_array();
		seg_init(0, n - 1);
		std::set<LL>().swap(Hash);
		for(int i = 0; i < n; ++i)
		{
			if(pos[sa[i]] == -1)
				continue;
			if(ht[i] > 0)
				check(i, ht[i]);
			check(i, sz[sa[i]]);
		}
		printf("%d\n", (int)Hash.size());
	}
	return 0;
}
