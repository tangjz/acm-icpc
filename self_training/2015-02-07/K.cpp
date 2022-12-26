#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10001;
map<int, int> Hash;
int n, tot, fa[maxn << 1], ans;
int idx(int x)
{
	if(Hash.find(x) != Hash.end())
		return Hash[x];
	return Hash[x] = tot++;
}
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d", &n) != EOF && n != -1)
	{
		tot = ans = 0;
		Hash.clear();
		for(int i = 0; i < maxn << 1; ++i)
			fa[i] = i;
		scanf("%d", &n);
		bool flag = 0;
		for(int i = 1; i <= n; ++i)
		{
			int l, r;
			char op[5];
			scanf("%d%d%s", &l, &r, op);
			if(flag)
				continue;
			int x = idx(l - 1), y = idx(r);
			int fx1 = find(x), fx2 = find(x + n);
			int fy1 = find(y), fy2 = find(y + n);
			if(op[0] == 'e')
			{
				if(fx1 == fy2 || fx2 == fy1)
				{
					flag = 1;
					continue;
				}
				fa[find(fx1)] = find(fy1);
				fa[find(fx2)] = find(fy2);
			}
			else
			{
				if(fx1 == fy1 || fx2 == fy2)
				{
					flag = 1;
					continue;
				}
				fa[find(fx1)] = find(fy2);
				fa[find(fx2)] = find(fy1);
			}
			ans = i;
		}
		printf("%d\n", ans);
	}
	return 0;
}
