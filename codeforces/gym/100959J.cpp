#include <cstdio>
typedef long long LL;
const int mod = 1000000007;
int n, cnt2, sum, ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		sum += x - 1;
		cnt2 += x == 3;
	}
	if(sum != n - 2)
	{
		puts("0");
		return 0;
	}
	ans = 1;
	for(int i = 1; i <= n - 2; ++i)
	{
		int j = i;
		for( ; cnt2 && !(j & 1); --cnt2, j >>= 1);
		ans = (LL)ans * j % mod;
	}
	printf("%d\n", ans);
	return 0;
}
