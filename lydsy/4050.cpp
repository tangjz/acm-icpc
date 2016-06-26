#include <cstdio>
#include <algorithm>
const int maxn = 1001;
const char *out[] = {"clockwise", "counterclockwise"};
int t, n, x[maxn], y[maxn], r[maxn], fa[maxn], dis[maxn];
int sqr(int x)
{
	return x * x;
}
int find(int x)
{
	if(x == fa[x])
		return x;
	int tmp = fa[x];
	fa[x] = find(fa[x]);
	dis[x] ^= dis[tmp];
	return fa[x];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", x + i, y + i, r + i);
			fa[i] = i;
			dis[i] = 0;
		}
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
				if(sqr(x[i] - x[j]) + sqr(y[i] - y[j]) == sqr(r[i] + r[j]))
				{
					int u = find(i), v = find(j);
					if(u != v)
					{
						fa[u] = v;
						dis[u] = dis[i] ^ dis[j] ^ 1;
					}
				}
		for(int i = 0; i < n; ++i)
			if(find(0) == find(i))
				if(r[0] % r[i] == 0)
					printf("%d %s\n", r[0] / r[i], out[dis[i] ^ dis[0]]);
				else
				{
					int rr = std::__gcd(r[0], r[i]);
					printf("%d/%d %s\n", r[0] / rr, r[i] / rr, out[dis[i] ^ dis[0]]);
				}
			else
				puts("not moving");
	}
	return 0;
}
