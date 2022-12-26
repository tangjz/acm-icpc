/*
 * f[i][j] = f[i - 1][j - k] (1 <= k <= n / 2)
 * 直观即可知 滚动
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int n, f[2501];
int main()
{
	int i, j, k, m, tmp;
	scanf("%d", &n);
	m = n / 2 - (~n & 1);
	f[0] = 1;
	for(k = 0; k <= 3; ++k)
		for(i = n; i >= 0; --i)
		{
			f[i] = 0;
			tmp = min(i, m);
			for(j = 1; j <= tmp; ++j) f[i] += f[i - j];
		}
	printf("%d\n", f[n]);
	return 0;
}
