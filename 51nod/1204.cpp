#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100001;
int n, m, dsu[maxn], dis[maxn];
int dsu_find(int x)
{
	if(dsu[x] < 0)
		return x;
	int fa = dsu[x];
	dsu[x] = dsu_find(fa);
	dis[x] ^= dis[fa];
	return dsu[x];
}
bool dsu_merge(int u, int v, int w)
{
	int x = dsu_find(u), y = dsu_find(v);
	if(x == y)
		return !(dis[u] ^ dis[v] ^ w);
	if(dsu[x] > dsu[y])
		std::swap(x, y);
	if(dsu[x] == dsu[y])
		--dsu[x];
	dsu[y] = x;
	dis[y] = dis[u] ^ dis[v] ^ w;
	return 1;
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(dsu, -1, (n + 1) * sizeof(int));
	for(int i = 1; i <= m; ++i)
	{
		int x, y;
		char op[5];
		scanf("%d%d%s", &x, &y, op);
		if(!dsu_merge(x - 1, y, op[0] == 'o'))
		{
			printf("%d\n", i);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
