#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1000001, maxp = 78499, maxs = 31623;
int tot, pr[maxp], d[maxn], sz, que[maxs];
LL f[maxn], val[maxs];
LL calc(int x)
{
	if(x < maxn)
		return f[x];
	int idx = lower_bound(que, que + sz, x) - que;
	LL &ret = val[idx];
	if(ret)
		return ret;
	ret = x * (x + 1LL) >> 1;
	for(int i = 2, j, k; i <= x; i = j + 1)
	{
		k = x / i;
		j = x / k;
		ret -= (j - i + 1LL) * calc(k);
	}
	return ret;
}
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!f[i])
		{
			pr[tot++] = d[i] = i;
			f[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				f[k] = f[i] * pr[j];
				break;
			}
			else
				f[k] = f[i] * (pr[j] - 1);
		}
		f[i] += f[i - 1];
	}
	int n;
	scanf("%d", &n);
	for(int i = 1, j, k; i <= n; i = j + 1)
	{
		k = n / i;
		j = n / k;
		if(k >= maxn)
			que[sz++] = k;
	}
	reverse(que, que + sz);
	printf("%lld\n", calc(n));
	return 0;
}
