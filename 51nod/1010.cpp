#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 10917, maxp = 3, prime[maxp] = {2, 3, 5};
const LL maxv = (LL)1e18, lim[maxp] = {maxv / prime[0], maxv / prime[1], maxv / prime[2]};
int tot, t;
LL seq[maxn], x;
void dfs(int dep, LL val)
{
	if(dep == maxp)
		seq[tot++] = val;
	else
		for(dfs(dep + 1, val); val <= lim[dep]; dfs(dep + 1, val *= prime[dep]));
}
int main()
{
	dfs(0, 1);
	std::sort(seq, seq + tot);
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &x);
		printf("%lld\n", *std::lower_bound(seq + 1, seq + tot, x));
	}
	return 0;
}
