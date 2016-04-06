#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 41;
int n, w[3][3];
long long f[maxn][3][3];
int main()
{
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			scanf("%d", &w[i][j]);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < 3; ++j)
			for(int k = 0; k < 3; ++k) if(j != k)
			{
				int t = 3 - j - k;
				f[i][j][k] = min(f[i - 1][j][t] + w[j][k] + f[i - 1][t][k],
				f[i - 1][j][k] + w[j][t] + f[i - 1][k][j] + w[t][k] + f[i - 1][j][k]);
			}
	printf("%I64d\n", f[n][0][2]);
	return 0;
}
