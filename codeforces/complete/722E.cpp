#include <stdio.h>
#include <algorithm>
using namespace std;
#define x first
#define y second
typedef long long LL;
const int maxn = 2010, maxm = 100001, maxd = 21, mod = 1000000007;
int r, c, n, m, fact[maxm << 1], iact[maxm], f[maxd][maxn], g[maxn][maxn], ans;
pair<int, int> p[maxn];
int mod_inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int main()
{
	scanf("%d%d%d%d", &r, &c, &n, &m);
	fact[0] = 1;
	for(int i = 1; i <= r + c; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	iact[1] = 1;
	for(int i = 2, lim = max(r, c); i <= lim; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	iact[0] = 1;
	for(int i = 1, lim = max(r, c); i <= lim; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	p[0] = make_pair(1, 1);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &p[i].x, &p[i].y);
	p[n + 1] = make_pair(r, c);
	sort(p + 1, p + n + 1);
	for(int i = 1; i <= n + 1; ++i)
		for(int j = 0; j < i; ++j)
		{
			int dx = p[i].x - p[j].x, dy = p[i].y - p[j].y;
			g[i][j] = dx < 0 || dy < 0 ? 0 : (LL)fact[dx + dy] * iact[dx] % mod * iact[dy] % mod;
		}
	f[0][0] = 1;
	for(int d = 1; d < maxd; ++d)
		for(int i = 1; i <= n + 1; ++i)
			for(int j = 0; j < i; ++j)
			{
				f[d][i] = (f[d][i] + (LL)f[d - 1][j] * g[i][j]) % mod;
				if((f[d][i] = (f[d][i] - (LL)f[d][j] * g[i][j]) % mod) < 0)
					f[d][i] += mod;
			}
	ans = g[n + 1][0];
	for(int d = 1; d < maxd; ++d, m = m + 1 >> 1)
		ans = (ans + (m - 1LL) * f[d][n + 1]) % mod;
	ans = (LL)ans * mod_inv(g[n + 1][0]) % mod;
	printf("%d\n", ans);
	return 0;
}
