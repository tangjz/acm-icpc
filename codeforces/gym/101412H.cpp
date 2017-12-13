#include <bitset>
#include <cstdio>
const int maxn = 101, maxm = 10001;
int n, m;
struct Info
{
	int s, x, y;
	void read()
	{
		scanf("%d%d%d", &s, &x, &y);
		--x, --y;
	}
} que[maxm];
std::bitset<maxn> f[maxn], g[maxn];
bool check(int lim)
{
	for(int i = 0; i < n; ++i)
	{
		f[i].reset();
		f[i].set(i);
		g[i].reset();
	}
	for(int i = 0; i < lim; ++i)
		if(que[i].s <= 2)
		{
			f[que[i].x].set(que[i].y);
			if(que[i].s == 2)
				f[que[i].y].set(que[i].x);
		}
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			if(f[i].test(k))
				f[i] |= f[k];
	for(int i = 0; i < lim; ++i)
		if(que[i].s == 4)
			for(int j = 0; j < n; ++j)
			{
				if(f[j].test(que[i].x))
					g[j].set(que[i].y);
				if(f[j].test(que[i].y))
					g[j].set(que[i].x);
			}
	for(int i = 0; i < lim; ++i)
		if(que[i].s == 3)
		{
			if(f[que[i].x].test(que[i].y) && f[que[i].y].test(que[i].x)
			|| (f[que[i].x] & g[que[i].x]).any() && (f[que[i].y] & g[que[i].y]).any())
				return 0;
		}
		else if(que[i].s == 5)
		{
			if((f[que[i].x] & g[que[i].x]).any()
			|| (f[que[i].y] & g[que[i].y]).any()
			|| (f[que[i].y] & g[que[i].x]).any()
			|| (f[que[i].y] & g[que[i].y]).any())
				return 0;
		}
	return 1;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		for(int i = 0; i < m; ++i)
			que[i].read();
		int L = 1, R = m, M;
		while(L < R)
		{
			M = (L + R + 1) >> 1;
			if(check(M))
				L = M;
			else
				R = M - 1;
		}
		printf("%d\n", L);
	}
	return 0;
}
