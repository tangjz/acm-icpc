#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxs = 21;
int n, m, q, dsu[maxn], dis[maxn];
std::map<std::string, int> idx;
int dsu_find(int x)
{
	if(dsu[x] < 0)
		return x;
	int tp = dsu[x];
	dsu[x] = dsu_find(dsu[x]);
	dis[x] ^= dis[tp];
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
	scanf("%d%d%d", &n, &m, &q);
	memset(dsu, -1, n * sizeof(int));
	memset(dis, 0, n * sizeof(int));
	for(int i = 0; i < n; ++i)
	{
		static char s[maxs];
		scanf("%s", s);
		idx[s] = i;
	}
	while(m--)
	{
		int typ;
		static char s[maxs], t[maxs];
		scanf("%d%s%s", &typ, s, t);
		int u = idx[s], v = idx[t];
		puts(dsu_merge(u, v, --typ) ? "YES" : "NO");
	}
	while(q--)
	{
		static char s[maxs], t[maxs];
		scanf("%s%s", s, t);
		int u = idx[s], v = idx[t];
		int x = dsu_find(u), y = dsu_find(v);
		printf("%d\n", x == y ? (dis[u] == dis[v] ? 1 : 2) : 3);
	}
	return 0;
}
