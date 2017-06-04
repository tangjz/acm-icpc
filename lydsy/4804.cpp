#include <stdio.h>
typedef long long LL;
const int maxn = 10000001, maxp = 664579;
int tot, pr[maxp], d[maxn], dk[maxn], ot[maxn], phi[maxn];
LL f[maxn];
int main()
{
	f[1] = phi[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = dk[i] = i;
			ot[i] = 1;
			int pre = 1, pphi = 1, plim = (maxn - 1) / i;
			int cur = i, cphi = i - 1;
			while(pre <= plim)
			{
				phi[cur] = cphi;
				f[cur] = i * f[pre] + cphi - pphi;
				pre = cur;
				pphi = cphi;
				cur *= i;
				cphi *= i;
			}
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				dk[k] = dk[i] * pr[j];
				ot[k] = ot[i];
				break;
			}
			else
			{
				dk[k] = pr[j];
				ot[k] = i;
			}
		}
	}
	for(int i = 2; i < maxn; ++i)
		if(dk[i] != i)
		{
			phi[i] = phi[dk[i]] * phi[ot[i]];
			f[i] = f[dk[i]] * f[ot[i]];
		}
	for(int i = 1; i < maxn; ++i)
		f[i] = f[i - 1] + (f[i] << 1) - phi[i];
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%lld\n", f[n]);
	}
	return 0;
}
