#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 100001;
int n, m, a[maxn], b[maxn];
LL sum;
bool check(LL lim)
{
	int cnt = m;
	LL rem = 0;
	for(int i = n; i >= 1; --i)
	{
		if(a[i] <= rem)
		{
			rem -= a[i];
			continue;
		}
		if(lim <= i)
			return 0;
		LL val = (a[i] - rem - 1) / (lim - i) + 1, res = val * (lim - i) - a[i] + rem;
		if(cnt < val)
			return 0;
		cnt -= val;
		rem = res;
	}
	return 1;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		sum += a[i];
	}
	LL L = 1, R = sum + n;
	while(L < R)
	{
		LL M = L + R >> 1;
		if(check(M))
			R = M;
		else
			L = M + 1;
	}
	printf("%I64d\n", L);
	return 0;
}
