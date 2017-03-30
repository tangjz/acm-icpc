#include <cmath>
#include <stdio.h>
const int maxn = 11, maxm = 101;
int t, n, c[maxn];
double p[maxn];
long double pp[maxn], pre[maxn], ans[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%lf", c + i, p + i);
			pp[i] = 1;
			pre[i] = ans[i] = 0;
		}
		if(n == 1)
		{
			printf("%.6f\n", 1.0);
			continue;
		}
		for(int i = 1; i < maxm; ++i)
		{
			long double tmp = 0;
			for(int j = 0; j < n; ++j)
			{
				pp[j] *= p[j];
				tmp += c[j] * log(1 - pp[j]);
			}
			for(int j = 0; j < n; ++j)
			{
				long double tp = c[j] * log(1 - pp[j]), cur_j = exp(tmp - tp);
				ans[j] += (1 - exp(tp)) * (cur_j - pre[j]);
				pre[j] = cur_j;
			}
		}
		for(int i = 0; i < n; ++i)
			printf("%.6f%c", (double)ans[i], " \n"[i == n - 1]);
	}
	return 0;
}
