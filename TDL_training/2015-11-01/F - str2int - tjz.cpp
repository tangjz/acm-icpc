#include <stdio.h>
#include <cstring>
const int maxn = 110010, mod = 2012, inv9 = 1565;
int n, m, tot, c[maxn], sa[maxn], rk[maxn], ht[maxn], pos[maxn], pw[maxn], ans1[maxn], ans2[maxn], sum;
char s[maxn], temp[maxn];
void inc(int &x, int y)
{
    x += y;
    if(x >= mod)
        x -= mod;
}
void dec(int &x, int y)
{
    x -= y;
    if(x < 0)
        x += mod;
}
int main()
{
    pw[0] = 1;
    for(int i = 1; i < maxn; ++i)
        pw[i] = pw[i - 1] * 10 % mod;
	while(scanf("%d", &m) == 1)
	{
	    n = 0;
	    s[n++] = '0' - 2;
	    s[n] = '\0';
	    for(int i = 0; i < m; ++i)
	    {
	        scanf("%s", temp);
	        strcpy(s + n, temp);
	        int len = strlen(temp);
	        for(int j = 0; j < len; ++j)
                pos[n + j] = n + len;
	        n += len;
	        s[n++] = '0' - 2;
	        s[n] = '\0';
	    }
		int *x = rk, *y = ht, *t;
		tot = 256;
		memset(c, 0, tot * sizeof(int));
		for(int i = 0; i < n; ++i)
			++c[x[i] = s[i]];
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
		memset(ans1, 0, n * sizeof(int));
		memset(ans2, 0, n * sizeof(int));
        for(int i = 0; i < n; ++i)
        {
            if(s[sa[i]] <= '0')
                continue;
            int sta = sa[i], lcp = sa[i] + ht[i], lim = pos[sa[i]];
            if(lcp >= lim)
                continue;
            inc(ans1[lim - 1], pw[1]);
            dec(ans1[sta - 1], pw[lim - sta + 1]);
            if(sta < lcp)
            {
                dec(ans1[lcp - 1], pw[1]);
                inc(ans1[sta - 1], pw[lcp - sta + 1]);
            }
            dec(ans2[lim - 1], 1);
            inc(ans2[lcp - 1], 1);
        }
        sum = 0;
        for(int i = n - 1; i > 0; --i)
        {
            if(s[i] > '0')
                sum = (sum + (s[i] - '0') * (ans1[i] + ans2[i])) % mod;
            ans1[i - 1] = (ans1[i - 1] + ans1[i] * 10) % mod;
            ans2[i - 1] = (ans2[i - 1] + ans2[i]) % mod;
        }
        sum = sum * inv9 % mod;
        printf("%d\n", sum);
	}
	return 0;
}
