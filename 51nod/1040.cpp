#include <stdio.h>
typedef long long LL;
const int maxs = 10;
int n, cnt, s[maxs], c[maxs];
LL ans;
void dfs(int dep, int x, int phi)
{
	if(dep == cnt)
	{
		ans += n / x * phi;
		return;
	}
	for(int i = 0, now = 1; i <= c[dep]; ++i, now *= s[dep])
		dfs(dep + 1, x * now, phi * (now - now / s[dep]));
}
int main()
{
	scanf("%d", &n);
	int tmp = n;
	for(int i = 2; i <= tmp / i; ++i)
		if(tmp % i == 0)
		{
			for(c[cnt] = 0; tmp % i == 0; tmp /= i, ++c[cnt]) ;
			s[cnt++] = i;
		}
	if(tmp > 1)
	{
		c[cnt] = 1;
		s[cnt++] = tmp;
	}
	ans = 0;
	dfs(0, 1, 1);
	printf("%lld\n", ans);
	return 0;
}
