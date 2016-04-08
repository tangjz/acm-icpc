#include <cstdio>
typedef long long LL;
const int maxn = 100001;
int n, k, que[maxn], L, R;
LL s[maxn], f[maxn], g[maxn];
LL max(LL x, LL y)
{
	return x > y ? x : y;
}
int main()
{
	scanf("%d%d", &n, &k);
	que[R++] = 0;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", s + i);
		s[i] += s[i - 1];
		if(que[L] < i - k)
			++L;
		f[i] = s[i] + g[que[L]] - s[que[L]];
		g[i] = max(g[i - 1], f[i - 1]);
		while(L < R && g[que[R - 1]] - s[que[R - 1]] <= g[i] - s[i])
			--R;
		que[R++] = i;
	}
	printf("%lld\n", max(f[n], g[n]));
	return 0;
}
