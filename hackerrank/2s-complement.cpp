#include <stdio.h>
typedef long long LL;
const int maxd = 32;
int t, A, B;
inline LL trans(int x)
{
	return x < 0 ? (1LL << maxd) + x : x;
}
inline LL bits(int len)
{
	return len ? (LL)len << (len - 1) : 0;
}
inline LL solve(LL lim) // calc 0 <= bits(x) < lim
{
	LL ret = 0;
	for(int i = maxd, c = 0; i >= 0; --i)
		if((lim >> i) & 1)
			ret += bits(i) + ((LL)(c++) << i);
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &A, &B);
		printf("%lld\n", solve(trans(B) + 1) - solve(trans(A)) + (A < 0 && B >= 0 ? bits(maxd) : 0));
	}
	return 0;
}
