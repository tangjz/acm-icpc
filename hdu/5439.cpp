#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 438744 + 100, maxs = 3688 + 2, mod = 1000000007;
int last[maxn], sum[maxn], t, n, ans;
int num2(int L, int R)
{
	return (LL)(L + R) * (R - L + 1) / 2 % mod;
}
int main()
{
	last[1] = 1;
	sum[1] = 1;
	last[2] = 3;
	sum[2] = 11;
	for(int i = 3; i < maxn; ++i)
	{
		int cnt = lower_bound(last + 1, last + i + 1, i) - last;
		last[i] = last[i - 1] + cnt;
		sum[i] = (sum[i - 1] + (LL)i * num2(last[i - 1] + 1, last[i])) % mod;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		int pos = upper_bound(last + 1, last + maxn, n) - last - 1;
		ans = (sum[pos] + (LL)(pos + 1) * num2(last[pos] + 1, n)) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
