#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 500010, maxd = 20;
int n, q, len, slen[maxn], sa[maxn], rk[maxn], ht[maxn], st[maxn][maxd], Log[maxn], m, f[maxn], g[maxn], c[maxn];
int pos[maxn], val[maxn], bit[maxn], l[maxn], r[maxn], que[maxn << 1], id[maxn << 1], ans[maxn];
char str[maxn];
bool cmp(const int &x, const int &y)
{
	return que[x] < que[y];
}
void add(int x)
{
	for( ; x <= n; x += x & -x)
		++bit[x];
}
int sum(int x)
{
	int res = 0;
	for( ; x > 0; x -= x & -x)
		res += bit[x];
	return res;
}
int lcp(int L, int R)
{
	if(L == R)
		return maxn;
	++L;
	int k = Log[R - L + 1];
	return min(st[L][k], st[R - (1 << k) + 1][k]);
}
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void print(int x, char ch = '\n')
{
	int len, num[10];
	for(len = 0; x; num[len++] = x % 10, x /= 10);
	if(!len)
		num[len++] = 0;
	while(len)
		putchar('0' + num[--len]);
	putchar(ch);
}
int main()
{
	scan(n), scan(q);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", str + len);
		slen[i] = strlen(str + len);
		pos[i] = len;
		for(int k = 0; k < slen[i]; ++k)
			val[len + k] = i;
		len += slen[i];
		str[len++] = '$';
	}
	m = 256;
	int *x = f, *y = g;
	for(int i = 0; i < m; ++i)
		c[i] = 0;
	for(int i = 0; i < len; ++i)
		++c[x[i] = str[i]];
	for(int i = 1; i < m; ++i)
		c[i] += c[i - 1];
	for(int i = len - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for(int k = 1; k <= len; k <<= 1)
	{
		int p = 0;
		for(int i = len - k; i < len; ++i)
			y[p++] = i;
		for(int i = 0; i < len; ++i)
			if(sa[i] >= k)
				y[p++] = sa[i] - k;
		for(int i = 0; i < m; ++i)
			c[i] = 0;
		for(int i = 0; i < len; ++i)
			++c[x[y[i]]];
		for(int i = 0; i < m; ++i)
			c[i] += c[i - 1];
		for(int i = len - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1;
		x[sa[0]] = 0;
		for(int i = 1; i < len; ++i)
			x[sa[i]] = (y[sa[i - 1]] == y[sa[i]]
			&& (sa[i - 1] + k < len ? y[sa[i - 1] + k] : -1) == (sa[i] + k < len ? y[sa[i] + k] : -1) ? p - 1 : p++);
		if(p >= len)
			break;
		m = p;
	}
	for(int i = 0; i < len; ++i)
		rk[sa[i]] = i;
	for(int i = 0, j, k = 0; i < len; ++i)
	{
		if(k)
			--k;
		if(!rk[i])
			continue;
		for(j = sa[rk[i] - 1]; i + k < len && j + k < len && str[i + k] == str[j + k]; ++k);
		ht[rk[i]] = k;
	}
	for(int i = 2; i <= len; ++i)
		Log[i] = Log[i >> 1] + 1;
	for(int i = 0; i < len; ++i)
		st[i][0] = ht[i];
	for(int d = 1; 1 << d <= len; ++d)
		for(int i = 0; i + (1 << d - 1) < len; ++i)
			st[i][d] = min(st[i][d - 1], st[i + (1 << d - 1)][d - 1]);
	for(int i = 0; i < q; ++i)
	{
		int k, L, R, M, tmp;
		scan(l[i]), scan(r[i]), scan(k);
		tmp = rk[pos[k]];
		L = 0, R = tmp;
		while(L < R)
		{
			M = L + R >> 1;
			if(lcp(M, tmp) >= slen[k])
				R = M;
			else
				L = M + 1;
		}
		que[i + i] = L - 1;
		id[i + i] = i + i;
		L = tmp, R = len - 1;
		while(L < R)
		{
			M = L + R + 1 >> 1;
			if(lcp(tmp, M) >= slen[k])
				L = M;
			else
				R = M - 1;
		}
		que[i + i + 1] = L;
		id[i + i + 1] = i + i + 1;
	}
	sort(id, id + q + q, cmp);
	int j = 0;
	while(j < q + q && que[id[j]] == -1)
		++j;
	for(int i = 0; i < len; ++i)
	{
		if(val[sa[i]])
			add(val[sa[i]]);
		while(j < q + q && que[id[j]] == i)
		{
			if(id[j] & 1)
				ans[id[j] >> 1] += sum(r[id[j] >> 1]) - sum(l[id[j] >> 1] - 1);
			else
				ans[id[j] >> 1] -= sum(r[id[j] >> 1]) - sum(l[id[j] >> 1] - 1);
			++j;
		}
	}
	for(int i = 0; i < q; ++i)
		print(ans[i]);
	return 0;
}
