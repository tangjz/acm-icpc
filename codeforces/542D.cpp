#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxm = 1000001, maxn = 6721, maxd = 39;
int tot, pr[maxm], d[maxm], ftot, ptot, f[2][maxn], cur, pre = 1;
LL n, fact[maxn], pp[maxn];
int main()
{
	scanf("%I64d", &n);
	int lim = (LL)ceil(sqrt(n));
	fact[ftot++] = 1;
	for(int i = 2; i <= lim; ++i)
	{
		if(n % i == 0)
			fact[ftot++] = i;
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= lim; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	for(int i = ftot - 1 - (fact[ftot - 1] * fact[ftot - 1] == n); i >= 0; --i)
		fact[ftot++] = n / fact[i];
	for(int i = 1; i < ftot; ++i)
	{
		LL val = fact[i] - 1, p = 0;
		for(int j = 0; j < tot && (LL)pr[j] * pr[j] <= val; ++j)
			if(val % pr[j] == 0)
			{
				if(!p)
					p = pr[j];
				else
				{
					p = -1;
					break;
				}
				do { val /= pr[j]; } while(val % pr[j] == 0);
			}
		if(val > 1)
			p = p ? -1 : val;
		if(p > 0)
			pp[ptot++] = p;
	}
	std::sort(pp, pp + ptot);
	ptot = std::unique(pp, pp + ptot) - pp;
	f[cur][0] = 1;
	for(int i = 0; i < ptot; ++i)
	{
		cur ^= 1;
		pre ^= 1;
		memcpy(f[cur], f[pre], ftot * sizeof(int));
		for(LL p = pp[i], plim = (n - 1) / pp[i]; ; p *= pp[i])
		{
			if(n % (p + 1) == 0)
			{
				LL vlim = n / (p + 1);
				for(int j = 0; fact[j] <= vlim; ++j)
					if(vlim % fact[j] == 0 && f[pre][j])
					{
						int k = std::lower_bound(fact, fact + ftot, fact[j] * (p + 1)) - fact;
						f[cur][k] += f[pre][j];
					}
			}
			if(p > plim)
				break;
		}
	}
	printf("%d\n", f[cur][ftot - 1]);
	return 0;
}
