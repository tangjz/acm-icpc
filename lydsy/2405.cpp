#include <cstdio>
typedef long long LL;
const int maxn = 22680;
int s[maxn + 1];
LL calc(LL n)
{
	return n / maxn * s[maxn] + s[n % maxn];
}
int main()
{
	for(int i = 1, j = 1; i <= maxn; ++i, j = j < 9 ? j + 1 : 1)
		if(i * j <= maxn)
			s[i * j] = 1;
	for(int i = 1; i <= maxn; ++i)
		s[i] += s[i - 1];
	int t;
	LL L, R;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &L, &R);
		printf("%lld\n", calc(R) - calc(L - 1));
	}
	return 0;
}
