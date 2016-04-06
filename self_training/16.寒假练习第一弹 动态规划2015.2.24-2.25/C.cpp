#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 62501;
int t, p, q, pos[maxn], f[maxn], ans;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		ans = 0;
		memset(f, 0, sizeof f);
		memset(pos, 0, sizeof pos);
		scanf("%*d%d%d", &p, &q);
		++p;
		for(int i = 1, x; i <= p; ++i)
		{
			scanf("%d", &x);
			pos[x] = i;
		}
		for(int i = 0, x, k; i <= q; ++i)
		{
			scanf("%d", &x);
			x = pos[x];
			if(!x)
				continue;
			f[k = lower_bound(f + 1, f + ans + 1, x) - f] = x;
			if(ans < k)
				ans = k;
		}
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
