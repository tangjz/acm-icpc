#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 1001;
int n, a[maxn][maxn], low[maxn], m, stk[maxn];
LL b[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 0; j <= a[i][0]; ++j)
			scanf("%d", a[i] + j);
		std::sort(a[i] + 1, a[i] + a[i][0] + 1);
		low[i] = a[i][0] + 1;
		for(int j = 1; j <= a[i][0]; ++j)
			if(a[i][j] <= b[i] + 1)
				b[i] += a[i][j];
			else
			{
				low[i] = j;
				break;
			}
	}
	int t, x, y, z;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &x, &y, &z);
		ans = b[x];
		m = 0;
		for(int i = 1, j = 1, k = low[x]; i <= z; ++i)
		{
			for( ; j <= a[y][0] && a[y][j] <= ans + 1; ++j)
				stk[++m] = a[y][j];
			if(!m)
				break;
			ans += stk[m--];
			for( ; k <= a[x][0] && a[x][k] <= ans + 1; ++k)
				ans += a[x][k];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
