#include <stdio.h>
typedef long long LL;
int n, m, k;
bool check(int x)
{
	int L = x < k ? k - x + 1 : 1, R = x < n - k + 1 ? k + x - 1 : n;
	return L - 1 + n - R + (((x - (k - L) + (x - 1)) * (LL)(k - L)) >> 1) + (((x + x - (R - k)) * (LL)(R - k + 1)) >> 1) <= m;
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	int L = 1, R = m;
	while(L < R)
	{
		int M = (L + R + 1) >> 1;
		if(check(M))
			L = M;
		else
			R = M - 1;
	}
	printf("%d\n", L);
	return 0;
}
