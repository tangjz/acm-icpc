/*
 * 将原串复制一遍，求后缀数组即可
 */
#include <cstdio>
#include <cstring>
const int maxn = 200002;
char s[maxn];
int cnt, tran[256], len, x[maxn], y[maxn], c[maxn], sa[maxn];
int main()
{
	scanf("%s", s);
	len = strlen(s);
	for(int i = 0; i < len; ++i)
	{
		if(!tran[s[i]])
		{
			++cnt;
			tran[s[i]] = 1;
		}
		s[len + i] = s[i];
	}
	len <<= 1;
	for(int i = 0, j = 0; i < 256; ++i)
		if(tran[i]) tran[i] = j++;
	for(int i = 0; i < len; ++i)
		++c[x[i] = tran[s[i]]];
	for(int i = 1; i < cnt; ++i)
		c[i] += c[i - 1];
	for(int i = len - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for(int k = 1; k <= len; k <<= 1)
	{
		int tmp = 0;
		for(int i = len - k; i < len; ++i)
			y[tmp++] = i;
		for(int i = 0; i < len; ++i)
			if(sa[i] >= k) y[tmp++] = sa[i] - k;
		memset(c, 0, sizeof c);
		for(int i = 0; i < len; ++i)
			++c[x[y[i]]];
		for(int i = 1; i < cnt; ++i)
			c[i] += c[i - 1];
		for(int i = len - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		memcpy(y, x, sizeof x);
		cnt = 1;
		x[sa[0]] = 0;
		for(int i = 1; i < len; ++i)
			if(y[sa[i - 1]] == y[sa[i]] && (sa[i - 1] + k < len ? y[sa[i - 1] + k] : -1) == (sa[i] + k < len ? y[sa[i] + k] : -1)) x[sa[i]] = cnt - 1;
			else x[sa[i]] = cnt++;
		if(cnt >= len) break;
	}
	for(int i = 0; i < len; ++i)
		if(sa[i] < len >> 1) putchar(s[(sa[i] ? sa[i] : len >> 1) - 1]);
	putchar('\n');
	return 0;
}
