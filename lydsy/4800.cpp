#include <stdio.h>
#include <algorithm>
#include <functional>
typedef long long LL;
const int maxn = 41, maxs = 1 << (maxn >> 1) | 1;
int n, nL, nR, lbt[maxs];
LL m, a[maxn], vL[maxs], vR[maxs], ans;
int main()
{
	for(int i = 1; i < maxs; ++i)
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
	scanf("%d%lld", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%lld", a + i);
	nL = n >> 1;
	for(int i = 1; i < 1 << nL; ++i)
	{
		int j = i & -i;
		vL[i] = vL[i ^ j] + a[lbt[j]];
	}
	std::sort(vL, vL + (1 << nL));
	nR = n - nL;
	for(int i = 1; i < 1 << nR; ++i)
	{
		int j = i & -i;
		vR[i] = vR[i ^ j] + a[nL + lbt[j]];
	}
	std::sort(vR, vR + (1 << nR), std::greater<LL>());
	for(int i = 0, j = 0; i < 1 << nR; ++i)
	{
		for( ; j < 1 << nL && vL[j] + vR[i] <= m; ++j);
		ans += j;
	}
	printf("%lld\n", ans);
	return 0;
}
