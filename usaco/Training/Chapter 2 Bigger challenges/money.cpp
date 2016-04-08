/*
ID: tangjin2
LANG: C++
TASK: money
*/
#include <cstdio>
const int maxn = 25, maxm = 10001;
int n, m, w;
long long f[maxm];
int main()
{
	freopen("money.in", "r", stdin);
	freopen("money.out", "w", stdout);
	scanf("%d%d", &n, &m);
	f[0] = 1;
	while(n--)
	{
		scanf("%d", &w);
		for(int i = w; i <= m; ++i)
			f[i] += f[i - w];
	}
	printf("%lld\n", f[m]);
	return 0;
}
