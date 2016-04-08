/*
 * \sum_{i = 1}^n{k mod i} = \sum_{i = 1}^n{k - [k / i] * i}
 * [k / i]只有\sqrt{k}种取值 
 */
#include <cstdio>
typedef long long LL;
LL n, k, ans;
int main()
{
	scanf("%lld%lld", &n, &k);
	ans = n * k;
	if(n > k) n = k;
	for(LL i = 1, j; i <= n; i = j + 1)
	{
		j = k / (k / i);
		if(j > n) j = n;
		ans -= (k / i) * (i + j) * (j - i + 1) / 2;
	}
	printf("%lld\n", ans);
	return 0;
}
