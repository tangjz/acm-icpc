#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int n, g[maxn], ans;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		ans = 0;
		memset(g, 0, sizeof g);
		for(int i = 1, j; i <= n; ++i)
		{
			scanf("%d", &j);
			int k = lower_bound(g + 1, g + ans + 1, j) - g;
			g[k] = j;
			if(ans < k)
				ans = k;
		}
		printf("%d\n", ans);
	}
	return 0;
}
