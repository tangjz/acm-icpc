/*
 * 利用数学方法计算状态转移之间的概率
 * 博弈中每个人向最优策略进发
 * 注意游戏进行100次左右后精度变化小于10^-30
 */
#include <cstdio>
int t, n;
double p, q, f[105], g[105], e1, e2, e3, e4, e5, e6, e7, e8, tmp;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%lf%lf", &n, &p, &q);
		if(n > 100) n = 100;//exp < 10^-30
		tmp = p + q - p * q;
		e1 = p / tmp; e2 = 1 - e1;
		e4 = q / tmp; e3 = 1 - e4;
		tmp = 1 - p * q;
		e5 = (1 - p) / tmp; e6 = 1 - e5;
		e8 = (1 - q) / tmp; e7 = 1 - e8;
		f[0] = 0; g[0] = 1;
		for(int i = 1; i <= n; ++i)
			if(f[i - 1] < g[i - 1])
			{
				f[i] = f[i - 1] * e2 + g[i - 1] * e1;
				g[i] = f[i - 1] * e4 + g[i - 1] * e3;
			}
			else
			{
				f[i] = f[i - 1] * e6 + g[i - 1] * e5;
				g[i] = f[i - 1] * e8 + g[i - 1] * e7;
			}
		printf("%.6lf\n", f[n]);
	}
	return 0;
}
