#include <set>
#include <vector>
#include <stdio.h>
#include <algorithm>
const int maxn = 1001, maxm = 1000001;
int deg[maxm], tot, out[maxm];
std::vector<int> e[maxm];
std::set<int> sp;
int main()
{
	int n;
	scanf("%d", &n);
	while(n--)
	{
		int m;
		scanf("%d", &m);
		for(int p = 0, x; m--; p = x)
		{
			scanf("%d", &x);
			++deg[x];
			e[p].push_back(x);
		}
	}
	sp.insert(0);
	while(sp.size() > 0)
	{
		int u = *sp.begin();
		sp.erase(u);
		out[tot++] = u;
		for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			if(!(--deg[*it]))
				sp.insert(*it);
	}
	for(int i = 1; i < tot; ++i)
		printf("%d%c", out[i], " \n"[i == tot - 1]);
	return 0;
}
