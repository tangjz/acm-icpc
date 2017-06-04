#include <cstdio>
const int maxn = 100001, maxm = 21;
int n, m, tot, pr[maxn], d[maxn], ans[maxm];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	for(tot = m; tot > 1 && n > 1; ans[tot--] = d[n], n /= d[n]);
	if(tot == 1 && n > 1)
	{
		ans[1] = n;
		for(int i = 1; i <= m; ++i)
			printf("%d%c", ans[i], " \n"[i == m]);
	}
	else
		puts("-1");
	return 0;
}
