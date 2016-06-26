#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 4001;
int n, mod, fib[2], f[2][maxn], cur, pre = 1, ans;
int main()
{
	scanf("%d%d", &n, &mod);
	fib[cur] = 1;
	f[cur][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		if((fib[cur] += fib[pre]) >= mod)
			fib[cur] -= mod;
		f[cur][0] = 0;
		memcpy(f[cur] + 1, f[pre], i * sizeof(int));
		for(int j = 0; j < i; ++j)
			if((f[cur][j] = (f[cur][j] - (LL)fib[cur] * f[pre][j]) % mod) < 0)
				f[cur][j] += mod;
	}
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		if((ans = (ans - (LL)f[cur][i] * x) % mod) < 0)
			ans += mod;
	}
	printf("%d\n", ans);
	return 0;
}
