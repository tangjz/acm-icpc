#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int n, m, fa[maxn], sz[maxn], ans;
vector<int> e[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		ans = 0;
		memset(fa, 0, sizeof fa);
		memset(sz, 0, sizeof sz);
		for(int i = 1; i <= n; ++i)
			e[i].clear();
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if(u > v)
				swap(u, v);
			e[v].push_back(u);
		}
		fa[1] = 1;
		for(int i = 2; i <= n; ++i)
			for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
			{
				int &pa = *it;
				if(!fa[i] && pa != 1)
					fa[i] = pa;
				else if(find(pa) != find(i))
					fa[i] = i;
			}
		for(int i = 2; i <= n; ++i)
			++sz[find(i)];
		for(int i = 2; i <= n; ++i)
			if(i == find(i))
				ans += sz[i] * (n - 1 - sz[i]);
		printf("%d\n", (ans >> 1) + (n - 1));
	}
	return 0;
}
