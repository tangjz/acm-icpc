/*
 * f[场数][胜数][分数]
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int n, l;
double p[201] = {}, f[201][201][401] = {}, ans = 0;
int main()
{
	int i, j, k, score;
	scanf("%d%d%d", &n, &l, &k);
	for(i = 1; i <= n; ++i)
	{
		scanf("%lf", &p[i]);
		p[i] /= 100.0;
	}
	f[0][0][min(n, k) + 200] = 1.0;
	for(i = 1; i <= n; ++i)
	{
		scanf("%d", &score);
		for(j = 0; j <= n; ++j)
			for(k = -n; k <= n; ++k)
				if(score == -1)
				{
					f[i][j][k + 200] += f[i - 1][j][k + 200] * (1 - p[i]);
					f[i][j + 1][max(k - 1, -n) + 200] += f[i - 1][j][k + 200] * p[i];
				}
				else
				{
					f[i][j][k + 200] += f[i - 1][j][k + 200] * (1 - p[i]);
					f[i][j + 1][min(k + score, n) + 200] += f[i - 1][j][k + 200] * p[i];
				}
	}
	for(i = l; i <= n; ++i)
		for(j = 0; j <= n; ++j) ans += f[n][i][j + 200];
	printf("%.6lf\n", ans);
	return 0;
}
