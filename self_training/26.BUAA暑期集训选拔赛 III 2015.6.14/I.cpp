#include <stdio.h>
#include <cstring>
const int maxn = 100001;
int n, m, tot, c[maxn], sa[maxn], rk[maxn], ht[maxn];
char s[maxn];
long long calc(int pos, int len)
{
	long long ret = len;
	for(int i = pos - 1, lcp = n; i >= 0; --i)
	{
		if(lcp > ht[i + 1])
			lcp = ht[i + 1];
		ret += lcp < len ? n - sa[i] : len;
	}
	for(int i = pos + 1, lcp = n; i < n; ++i)
	{
		if(lcp > ht[i])
			lcp = ht[i];
		ret += lcp < len ? lcp : len;
	}
	return ret;
}
int main()
{
	while(scanf("%d%d%s", &n, &m, s) == 3)
	{
		int *x = rk, *y = ht, *t;
		tot = 26;
		memset(c, 0, tot * sizeof(int));
		for(int i = 0; i < n; ++i)
			++c[x[i] = s[i] - 'a'];
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
			t = x, x = y, y = t;
			p = 1;
			x[sa[0]] = 0;
			for(int i = 1; i < n; ++i)
				x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && (sa[i - 1] + k < n ? y[sa[i - 1] + k] : -1) == (sa[i] + k < n ? y[sa[i] + k] : -1) ? p - 1 : p++;
			if(p >= n)
				break;
			tot = p;
		}
		for(int i = 0; i < n; ++i)
			rk[sa[i]] = i;
		for(int i = 0, j, k = 0; i < n; ++i)
		{
			if(!rk[i])
			{
				ht[rk[i]] = 0;
				continue;
			}
			for(j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
			ht[rk[i]] = k;
			if(k)
				--k;
		}
		int pL = 0, pR = n, pM;
		while(pL < pR)
		{
			pM = pL + pR >> 1;
			if(calc(pM, n - sa[pM]) >= m)
				pR = pM;
			else
				pL = pM + 1;
		}
		if(pL == n)
		{
			puts("No such substring.");
			continue;
		}
		int qL = 1, qR = n - sa[pL], qM;
		while(qL < qR)
		{
			qM = qL + qR >> 1;
			if(calc(pL, qM) >= m)
				qR = qM;
			else
				qL = qM + 1;
		}
		s[sa[pL] + qL] = '\0';
		puts(s + sa[pL]);
	}
	return 0;
}
