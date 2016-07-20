#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int t, n, k, prime[maxn], tot, seq[12], pow2[12], tmp, tmp2, ans;
void dfs(int dep, int sum, int cnt)
{
	if(dep == tot)
	{
		if(cnt & 1)
			tmp += pow2[cnt - 1] * (n / sum);
		else if(cnt > 0)
			tmp -= pow2[cnt - 1] * (n / sum);
		return;
	}
	dfs(dep + 1, sum, cnt);
	dfs(dep + 1, sum * seq[dep], cnt + 1);
}
void add(int dep, int sum, int cnt, int last)
{
	if(sum > n)
		return;
	{
		if(cnt & 1)
			tmp2 += pow2[cnt - 1] * (n / sum);
		else if(cnt > 0)
			tmp2 -= pow2[cnt - 1] * (n / sum);
		if(dep == tot)
			return;
	}
	for(int i = last; i < tot; ++i)
		add(dep + 1, sum * seq[i], cnt + 1, i + 1);
}
int main()
{
	pow2[0] = 1;
	for(int i = 1; i < 12; ++i)
		pow2[i] = pow2[i - 1] << 1;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= k; ++i)
			scanf("%d", &prime[i]);
		sort(prime + 1, prime + k + 1);
		int mid = 0;
		for(int i = 1; i <= k; ++i)
			if(prime[i] * prime[i] <= n)
				mid = i;
		ans = 0;
		for(int i = 0; i < (1 << mid); ++i)
		{
			tot = 0;
			for(int j = 1; j <= mid; ++j)
				if(i & (1 << j - 1))
					seq[tot++] = prime[j];
			tmp = 0;
			dfs(0, 1, 0);
			for(int j = mid + 1; j <= k; ++j)
			{
				tmp2 = 0;
				add(0, prime[j], 1, 0);
				if(tmp2 > 0)
					tmp += tmp2;
			}
			if(ans < tmp)
				ans = tmp;
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
