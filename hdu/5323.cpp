#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
const long long INF = 0x7f7f7f7f7f7f7f7f;
long long dfs(int dep, long long L, long long R)
{
	if(dep >= 22)
		return INF;
	if(L == 0)
		return R;
	if(L < 0 || 2 * L - R - 1 < 0)
		return INF;
	long long ret = min(min(dfs(dep + 1, L, 2 * R - L), dfs(dep + 1, 2 * L - R - 2, R)),
	min(dfs(dep + 1, L, 2 * R - L + 1), dfs(dep + 1, 2 * L - R - 1, R)));
	return ret;
}
int main()
{
	int L, R;
	while(scanf("%d%d", &L, &R) == 2)
	{
		long long ans = dfs(0, L, R);
		printf("%lld\n", ans == INF ? -1 : ans);
	}
	return 0;
}
