#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 316229, maxs = 11;
int tot, prime[maxn], last[maxn], n, sqn, T, cnt, d[maxs], qL, qR;
LL tmp, ans;
LL calc1(int L, int R)
{
	LL ret = 0;
	for(int i = L; i <= R; ++i)
	{
		bool flag = 1;
		for(int j = 1; j <= cnt; ++j)
			if(i % d[j] == 0)
			{
				flag = 0;
				break;
			}
		if(flag)
			ret += T / i;
	}
	return ret;
}
void dfs(int dep, int sum, int sgn)
{
	if(dep > cnt)
	{
		int L = (qL - 1) / sum, R = qR / sum, TT = T / sum;
		for(int x = max(TT / R, 1); x <= TT / L; ++x)
			tmp += sgn * (LL)x * (min(TT / x, R) - max(TT / (x + 1), L));
		return;
	}
	dfs(dep + 1, sum, sgn);
	dfs(dep + 1, sum * d[dep], -sgn);
}
LL calc2(int L, int R)
{
	qL = L;
	qR = R;
	tmp = 0;
	dfs(1, 1, 1);
	return tmp;
}
int main()
{
	scanf("%d", &n);
	sqn = (int)ceil(sqrt(n));
	for(int i = 2; i <= sqn; ++i)
	{
		if(!last[i])
			prime[tot++] = last[i] = i;
		for(int j = 0, k = sqn / i; j < tot && prime[j] <= k; ++j)
		{
			last[i * prime[j]] = last[i];
			if(i % prime[j] == 0)
				break;
		}
	}
	for(int i = 2; i + 1 <= (T = n / i); ++i)
	{
		cnt = 0;
		for(int x = i; x > 1; x /= last[x])
			if(d[cnt] != last[x])
				d[++cnt] = last[x];
		int sz = (int)sqrt((1 << cnt) * (double)T / cnt);
		if(sz <= i)
			ans += calc2(i + 1, 2 * i - 1);
		else if(sz + 1 >= 2 * i)
			ans += calc1(i + 1, 2 * i - 1);
		else
			ans += calc1(i + 1, sz) + calc2(sz + 1, 2 * i - 1);
	}
	printf("%lld\n", ans);
	return 0;
}
