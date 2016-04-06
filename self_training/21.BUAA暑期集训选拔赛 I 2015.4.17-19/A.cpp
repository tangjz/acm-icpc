#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int n, m, f[maxn][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", &f[i][j]);
	for(int d = n + m - 2; d >= 0; --d)
		for(int j = max(d - m + 1, 0); j <= min(d, n - 1); ++j)
		{
			int k = d - j;
			if(k + 1 < m)
				f[j][k] = min(f[j][k], f[j][k + 1]);
			if(j + 1 < n)
				f[j][k] = min(f[j][k], f[j + 1][k]);
			if(j - 1 >= 0 && k + 1 < m)
				f[j][k] = min(f[j][k], f[j - 1][k + 1]);
		}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			printf("%d%c", f[i][j], " \n"[j == m - 1]);
	return 0;
}
