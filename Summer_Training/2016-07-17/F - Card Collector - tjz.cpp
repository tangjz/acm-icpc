#include <cstdio>
const int maxn = 20;
int n;
double p[maxn], f[1 << maxn];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
			scanf("%lf", p + i);
		int all = (1 << n) - 1;
		f[all] = 0;
		for(int msk = all - 1; msk >= 0; --msk)
		{
			double val = 1, pro = 0;
			for(int i = 0; i < n; ++i)
				if(~(msk >> i) & 1)
				{
					val += p[i] * f[msk | (1 << i)];
					pro += p[i];
				}
			f[msk] = val / pro;
		}
		printf("%.7f\n", f[0]);
	}
	return 0;
}
