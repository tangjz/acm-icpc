#include <stdio.h>
typedef long long LL;
const int maxn = 21, maxm = 41;
int x, y;
LL c[maxm][maxm], sei[maxm];
int main()
{
	scanf("%d%d", &x, &y);
	for(int i = 0; i < x + y; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	for(int i = 0; i < x; ++i) // (i, y) (i < x) <- (i, y-1) : p^i (1-p)^y C(y-1+i,i) * i
	{
		LL dt = c[y - 1 + i][i] * i;
		for(int j = 0; j <= y; ++j)
			sei[i + j] += (j & 1 ? -dt : dt) * c[y][j];
	}
	for(int i = 0; i < y; ++i) // (x, i) (i < y) <- (x-1, i) : p^x (1-p)^i (x-1+i)!/(x-1)!/i! * x
	{
		LL dt = c[x - 1 + i][i] * x;
		for(int j = 0; j <= i; ++j)
			sei[x + j] += (j & 1 ? -dt : dt) * c[i][j];
	}
	double ans = 0;
	for(int i = 0; i < x + y; ++i)
		ans += sei[i] / (i + 1.0);
	printf("%.6f\n", ans);
	return 0;
}
