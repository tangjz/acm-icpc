#include <set>
#include <map>
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 300001;
int n, q, fa[maxn], pos[maxn], tot, cnt;
set<int> e[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= q; ++i)
		fa[i] = i;
	for(int i = 1; i <= q; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(x == 1)
		{
			++cnt;
			e[y].insert(cnt);
			pos[cnt] = y;
			++tot;
		}
		else if(x == 2)
		{
			//for(auto it : e[y])
			for(set<int>::iterator it = e[y].begin(); it != e[y].end(); ++it)
			{
				fa[*it] = find(*it - 1);
				--tot;
			}
			e[y].clear();
		}
		else
		{
			for(int R = find(y); R > 0; R = find(R))
			{
				e[pos[R]].erase(R);
				--tot;
				fa[R] = find(R - 1);
			}
		}
		printf("%d\n", tot);
	}
	return 0;
}