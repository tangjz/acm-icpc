#include <stdio.h>
typedef long long LL;
const int maxp = 100001, maxc = 21, maxe = 61;
int tot, pr[maxp], d[maxp], cnt, p[maxc], e[maxc];
LL n, a, b, pp[maxc][maxe], ans;
void dfs(int dep, int mu, LL d0, LL d1, LL d2)
{
	LL lim1 = a / d1, lim2 = b / d2;
	if(dep == cnt)
	{
		mu > 0 ? ans += lim1 * lim2 : ans -= lim1 * lim2;
		return;
	}
	for(int i = 0; i <= e[dep]; ++i)
	{
		if(pp[dep][i] > lim1)
			break;
		if(pp[dep][e[dep] - i] <= lim2)
		{
			dfs(dep + 1, mu, d0, d1 * pp[dep][i], d2 * pp[dep][e[dep] - i]);
			if(i > 0)
				dfs(dep + 1, -mu, d0 * p[dep], d1 * pp[dep][i], d2 * pp[dep][e[dep] - i + 1]);
		}
	}
}
void solve()
{
	cnt = 0;
	for(int i = 0; i < tot && (LL)pr[i] * pr[i] <= n; ++i)
		if(n % pr[i] == 0)
		{
			for(e[cnt] = 1, n /= pr[i]; n % pr[i] == 0; ++e[cnt], n /= pr[i]);
			p[cnt++] = pr[i];
		}
	if(n > 1)
	{
		e[cnt] = 1;
		p[cnt++] = n;
	}
	ans = 0;
	for(int i = 0; i < cnt; ++i)
	{
		pp[i][0] = 1;
		for(int j = 1; j <= e[i]; ++j)
			pp[i][j] = pp[i][j - 1] * p[i];
	}
	dfs(0, 1, 1, 1, 1);
}
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int N, L1, L2, R1, R2;
	LL res = 0;
	scanf("%d%d%d%d%d", &N, &L1, &R1, &L2, &R2);
	n = N, a = R1, b = R2, solve(), res += ans;
	n = N, a = L1 - 1, b = R2, solve(), res -= ans;
	n = N, a = R1, b = L2 - 1, solve(), res -= ans;
	n = N, a = L1 - 1, b = L2 - 1, solve(), res += ans;
	printf("%lld\n", res);
	return 0;
}
