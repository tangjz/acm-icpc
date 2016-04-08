#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1000002, mod = 1000000007;
int n, m, p, fact[maxn], inv[maxn], s[maxn][3], f[maxn], g[maxn], ans;
int C(int n, int m)
{
	return n >= m ? (LL)fact[n] * inv[m] % mod * inv[n - m] % mod : 0;
}
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	if(n > m)
		swap(n, m);
	inv[1] = 1;
	for(int i = 2; i <= m + 1; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	fact[0] = inv[0] = 1;
	for(int i = 1; i <= m + 1; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	}
	--n;
	--m;
	for(int i = n; i >= 1; --i)
	{
		s[i][0] = (LL)(n / i) * (m / i) % mod;
		s[i][1] = (LL)(n / i) * (n / i + 1) / 2 * i % mod * (m / i) % mod;
		s[i][2] = (LL)(m / i) * (m / i + 1) / 2 * i % mod * (n / i) % mod;
		for(int j = i + i; j <= n; j += i)
		{
			s[i][0] -= s[i][0] < s[j][0] ? s[j][0] - mod : s[j][0];
			s[i][1] -= s[i][1] < s[j][1] ? s[j][1] - mod : s[j][1];
			s[i][2] -= s[i][2] < s[j][2] ? s[j][2] - mod : s[j][2];
		}
		f[i + 1] = (f[i + 1] + ((m + n + 1LL) * s[i][0] - s[i][1] - s[i][2]) * 4) % mod;
		f[i] = (f[i] - ((m + n + 3LL) * s[i][0] - s[i][1] - s[i][2]) * 4) % mod;
		g[i + 1] = (g[i + 1] + s[i][0] * 4LL) % mod;
	}
	++n;
	++m;
	for(int i = 1; i <= n; ++i)
	{
		int r = __gcd(i, m);
		f[r] = (f[r] - (n - i + 1) * 4) % mod;
		g[r + 1] = (g[r + 1] + (n - i + 1) * 2) % mod;
	}
	for(int i = 1; i < m; ++i)
	{
		int r = __gcd(i, n);
		f[r] = (f[r] - (m - i + 1) * 4) % mod;
		g[r + 1] = (g[r + 1] + (m - i + 1) * 2) % mod;
	}
	g[n + 1] = (g[n + 1] + m - 1) % mod;
	g[m + 1] = (g[m + 1] + n - 1) % mod;
	for(int i = p; i <= m + 1; ++i)
	{
		int coeff1 = C(i - 1, p - 1), coeff2 = (2LL * coeff1 - C(i - 2, p - 2)) % mod;
		ans = (ans + (LL)coeff1 * f[i] + (LL)coeff2 * g[i]) % mod;
	}
	ans = (ans + 2LL * C(n + 1, p) + 2LL * C(m + 1, p)) % mod;
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
