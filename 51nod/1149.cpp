#include <cmath>
#include <cstdio>
const int maxn = 1000010, mod = 1000000007;
const double pi = acos(-1);
typedef long long LL;
int n, inv[maxn], r[maxn], f[maxn], ans;
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}

int main()
{
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = (LL)inv[mod % i] * (mod - mod / i) % mod;
	scanf("%d", &n);
	if(n < 4)
	{
		puts("1");
		return 0;
	}
	f[0] = 1;
	for(int i = 0; i <= n - 3; ++i)
		r[i] = (int)ceil((n - i - 4) / pi);
	for(int i = 1; i <= n - 3; ++i)
	{
		int t1 = i + r[i], t2 = i - 1 + r[i - 1];
		if(n - i - r[i] * pi < 3)
			--t1;
		if(n - (i - 1) - r[i - 1] * pi < 3)
			--t2;
		switch(t1 - t2)
		{
			case -1 :
				f[i] = f[i - 1] * (t2 + 1LL - i) % mod * (t2 - i) % mod * inv[(LL)i * t2 % mod] % mod;
				break;
			case 0 :
				f[i] = f[i - 1] * (t2 + 1LL - i) % mod * inv[i] % mod;
				break;
			case 1 :
				f[i] = f[i - 1] * (t2 + 1LL) % mod * inv[i] % mod;
				break;
			case 2 :
				f[i] = f[i - 1] * (t2 + 2LL) % mod * (t2 + 1) % mod * inv[i * (t2 + 2LL - i) % mod] % mod;
		}
	}
	for(int i = 0; i <= n - 3; ++i)
		inc(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}
