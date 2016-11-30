#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 10000001, maxq = 1001, maxc = 10;
char mu[maxn];
int tot, prime[maxn / 12], d[maxn], f[maxn], c, p[maxc];
int q, mx, a[maxq], ord[maxq], sum, idx, ans, out[maxq];
bool cmp(const int &x, const int &y)
{
	return a[x] < a[y];
}
void dfs(int dep, int val)
{
	if(dep == c)
	{
		f[val] += mu[idx];
		mu[val] > 0 ? sum += f[val] : sum -= f[val];
		return;
	}
	dfs(dep + 1, val);
	dfs(dep + 1, val * p[dep]);
}
int main()
{
	scanf("%d", &q);
	for(int i = 0; i < q; ++i)
	{
		scanf("%d", a + i);
		if(mx < a[i])
			mx = a[i];
		ord[i] = i;
	}
	std::sort(ord, ord + q, cmp);
	mu[1] = 1;
	for(int i = 2; i <= mx; ++i)
	{
		if(!d[i])
		{
			mu[i] = -1;
			prime[tot++] = d[i] = i;
		}
		for(int j = 0, k = mx / i; prime[j] <= k; ++j)
		{
			int o = i * prime[j];
			d[o] = prime[j];
			if(d[i] == prime[j])
			{
				mu[o] = 0;
				break;
			}
			else
				mu[o] = -mu[i];
		}
	}
	for(int i = 0, o = 0; i <= mx; ++i)
	{
		if(mu[i])
		{
			c = 0;
			for(int tmp = i; d[tmp]; p[c++] = d[tmp], tmp /= d[tmp]);
			sum = 0;
			idx = i;
			dfs(0, 1);
			mu[i] > 0 ? ans += sum : ans -= sum;
		}
		for( ; o < q && a[ord[o]] == i; ++o)
			out[ord[o]] = ans;
	}
	for(int i = 0; i < q; ++i)
		printf("%d\n", out[i]);
	return 0;
}
