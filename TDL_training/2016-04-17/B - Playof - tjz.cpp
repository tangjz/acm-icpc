#include <map>
#include <cstdio>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;
const int maxn = (1 << 19) + 10, maxs = 21;
map<string, int> Hash;
int n, q, que[maxn], fa[maxn];
char e[maxn], s[maxs], t[maxs];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < 1 << n; ++i)
	{
		scanf("%s", s);
		Hash[(string)s] = i;
		que[i] = i;
	}
	scanf("%s", e);
	for(int i = 1, pos = 0; i <= n; ++i)
		for(int j = 0; j < 1 << n - i; ++j, ++pos)
		{
			int win = que[j << 1], los = que[j << 1 | 1];
			if(e[pos] == 'L')
				swap(win, los);
			fa[los] = win;
			que[j] = win;
		}
	fa[que[0]] = -1;
	scanf("%d", &q);
	while(q--)
	{
		scanf("%s%s", s, t);
		int u = Hash[(string)s], v = Hash[(string)t], w;
		assert(u != v);
		for(w = fa[v]; w != -1 && w != u; w = fa[w]);
		if(w == u)
		{
			puts("Win");
			continue;
		}
		for(w = fa[u]; w != -1 && w != v; w = fa[w]);
		if(w == v)
		{
			puts("Lose");
			continue;
		}
		puts("Unknown");
	}
	return 0;
}
