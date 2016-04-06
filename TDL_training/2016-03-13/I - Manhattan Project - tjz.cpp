#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n;
multiset<int> dis[1 << 4];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < 1 << 4; ++i)
			dis[i].clear();
		while(n--)
		{
			int t, x[4];
			scanf("%d", &t);
			for(int i = 0; i < 4; ++i)
				scanf("%d", x + i);
			if(t == 1)
			{
				for(int i = 0; i < 1 << 4; ++i)
				{
					int val = 0;
					for(int j = 0; j < 4; ++j)
						val += (i & (1 << j)) ? -x[j] : x[j];
					dis[i].insert(val);
				}
			}
			else if(t == 2)
			{
				for(int i = 0; i < 1 << 4; ++i)
				{
					int val = 0;
					for(int j = 0; j < 4; ++j)
						val += (i & (1 << j)) ? -x[j] : x[j];
					dis[i].erase(dis[i].find(val));
				}
			}
			else
			{
				int ans = -0x3f3f3f3f;
				for(int i = 0; i < 1 << 4; ++i)
				{
					int val = 0;
					for(int j = 0; j < 4; ++j)
						val += (i & (1 << j)) ? -x[j] : x[j];
					ans = max(ans, *dis[i].rbegin() - val);
				}
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
