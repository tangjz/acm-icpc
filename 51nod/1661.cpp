#include <stdio.h>
//#include <assert.h>
typedef long long LL;
const int maxn = 100000;
const LL maxv = 1000000000000000000LL;
LL sg(LL x, LL k)
{
	LL d = (x - 1) / k, r = (x - 1) % k + 1;
	return r == 1 ? (d ? sg(d, k) : 0) : x - d - 1;
}
int n;
LL m, a[maxn], SG;
int main()
{
	scanf("%d%lld", &n, &m);
	//assert(1 <= n && n <= maxn);
	//assert(1 <= m && m <= maxv);
	for(int i = 0; i < n; ++i)
	{
		scanf("%lld", a + i);
		//assert(1 <= a[i] && a[i] <= maxv);
		SG ^= sg(a[i], m);
	}
	if(!SG)
	{
		puts("Bob");
		return 0;
	}
	for(int i = 0; i < n; ++i)
	{
		LL p = SG ^ sg(a[i], m);
		LL q = p ? (p - 1) / (m - 1) * m + (p - 1) % (m - 1) + 2 : 1;
		if(q > a[i])
			continue;
		LL lim = (a[i] - 2) / m; // q * m + 1 <= a[i] - 1
		LL low = (a[i] - 1) / m + 1; // (a[i] - 1) / m + 1 <= q
		while(1)
		{
			if(q >= low)
			{
				//assert(sg(q, m) == p);
				//assert(low <= q && q < a[i]);
				printf("Alice %d %lld\n", i + 1, q);
				return 0;
			}
			if(q > lim)
				break;
			q = q * m + 1;
		}
	}
	return -1; // error!
}
