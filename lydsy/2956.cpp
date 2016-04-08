#include <cstdio>
#include <algorithm>
using namespace std;
const int mod = 19940417;
int n, m, ans;
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
void dec(int &x, int y)
{
	x -= y;
	if(x < 0)
		x += mod;
}
int sum(int l, int r)
{
	const int inv6 = 3323403;
	int ret = (long long)r * (r + 1) % mod * (r * 2 + 1) % mod;
	dec(ret, (long long)(l - 1) * l % mod * (l * 2 - 1) % mod);
	ret = (long long)ret * inv6 % mod;
	return ret;
}
int calc(int n)
{
	int ret = 0;
	inc(ret, (long long)n * n % mod);
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		dec(ret, (long long)(i + j) * (j - i + 1) / 2 % mod * (n / i) % mod);
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	if(n > m)
		swap(n, m);
	ans = (long long)calc(n) * calc(m) % mod;
	dec(ans, (long long)n * n % mod * m % mod);
	for(int i = 1, j = 1; i <= n; i = j + 1)
	{
		j = min(n / (n / i), m / (m / i));
		inc(ans, (long long)(i + j) * (j - i + 1) / 2 % mod * ((n / i * (long long)m + m / i * (long long)n) % mod) % mod);
		dec(ans, (long long)(n / i) * (m / i) % mod * sum(i, j) % mod);
	}
	printf("%d\n", ans);
	return 0;
}
