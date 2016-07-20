#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100010, maxs = 26;
int t, n, sa[maxn], rk[maxn], ma[maxn << 1], tot, lnk[maxn], fa[maxn];
char str[maxn];
struct Edge
{
	int nxt, v;
} e[maxn << 2];
inline void scan(int &x)
{
	register int ch;
	while((ch = getchar()) < '0' || ch > '9');
	for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
}
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scan(t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scan(n);
		tot = 0;
		memset(lnk, -1, n * sizeof(int));
		for(int i = 0; i < n; ++i)
		{
			scan(sa[i]);
			rk[sa[i]] = i;
			fa[i] = i;
		}
		rk[n] = -1;
		for(int i = 1; i < n; ++i)
			if(rk[sa[i - 1] + 1] > rk[sa[i] + 1])
			{
				e[tot] = (Edge){lnk[i], i - 1};
				lnk[i] = tot++;
			}
		ma[0] = -1;
		ma[1] = ma[n << 1 | 1] = 0;
		for(int i = 2; i <= n << 1; ++i)
			scan(ma[i]);
		bool flag = 1;
		for(int i = 2, mx = 1, id = 1; i <= n << 1 && flag; ++i)
		{
			int cur = mx > i ? std::min(mx - i, ma[(id << 1) - i] + 1) : 0, pL, pR;
			flag &= cur <= ma[i] + 1 && i - ma[i] > 0 && i + ma[i] < n + 1 << 1;
			for(pL = i - cur, pR = i + cur; cur <= ma[i] && flag; ++cur, --pL, ++pR)
				if((~pL & 1) && pL < pR)
				{
					int u = rk[(pL >> 1) - 1], v = rk[(pR >> 1) - 1];
					if(u > v)
						std::swap(u, v);
					for(u = find(u), v = find(v); u < v && flag; v = find(v))
					{
						for(int it = lnk[v]; it != -1 && flag; it = e[it].nxt)
							flag &= e[it].v < u;
						fa[v] = find(v - 1);
					}
				}
			if((flag &= (~pL & 1)) && pL >= 2 && pR <= n << 1)
			{
				pL = rk[(pL >> 1) - 1];
				pR = rk[(pR >> 1) - 1];
				if(pL > pR)
					std::swap(pL, pR);
				e[tot] = (Edge){lnk[pR], pL};
				lnk[pR] = tot++;
			}
			if(mx < i + cur)
			{
				mx = i + cur;
				id = i;
			}
		}
		char last = 'a';
		for(int i = 0, j = 0; i < n && flag; i = j)
		{
			char cur = last;
			for(++j; j < n && find(i) == find(j); ++j);
			for(int k = i; k < j && flag; ++k)
				for(int it = lnk[k]; it != -1 && flag; it = e[it].nxt)
					if(find(e[it].v) == find(i))
						flag = 0;
					else if(cur <= str[sa[e[it].v]])
						cur = str[sa[e[it].v]] + 1;
			if(cur > 'z')
				flag = 0;
			else
			{
				for( ; i < j; ++i)
					str[sa[i]] = cur;
				last = cur;
			}
		}
		str[n] = '\0';
		if(!flag)
			printf("Case #%d: Wrong calculation!\n", Case);
		else
			printf("Case #%d: %s\n", Case, str);
	}
	return 0;
}
