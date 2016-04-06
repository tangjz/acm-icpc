#include <cstdio>
typedef long long LL;
const int mod = 985661441, gen = 3, maxlen = 18, maxn = 1 << maxlen - 1;
int w[maxlen], x[maxn], y[maxn], n;
int pow(int x, int k, int p)
{
	int ret = 1;
	for( ; k; k >>= 1)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
	}
	return ret;
}
template<class T> void swap(T& x, T& y)
{
	T t = x;
	x = y;
	y = t;
}
void Rader(int x[], int len)
{
	for(int i = 1, j = len >> 1, k; i < len - 1; ++i)
	{
		if(i < j)
			swap(x[i], x[j]);
		k = len >> 1;
		while(j >= k)
		{
			j -= k;
			k >>= 1;
		}
		if(j < k)
			j += k;
	}
}
void NTT(int x[], int len, int flag)
{
	Rader(x, len);
	for(int i = 1, d = 2; d <= len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d)
			for(int k = j, ww = 1; k < j + d / 2; ++k)
			{
				int u = x[k], t = (LL)ww * x[k + d / 2] % mod;
				x[k] = u + t;
				if(x[k] >= mod)
					x[k] -= mod;
				x[k + d / 2] = u - t;
				if(x[k + d / 2] < 0)
					x[k + d / 2] += mod;
				ww = (LL)ww * w[i] % mod;
			}
	if(flag)
	{
		for(int i = 1; i < len / 2; ++i)
			swap(x[i], x[len - i]);
		int inv = pow(len, mod - 2, mod);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * inv % mod;
	}
}
void Conv(int x[], int y[], int len)
{
	NTT(x, len, 0);
	NTT(y, len, 0);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * y[i] % mod;
	NTT(x, len, 1);
}
char str[maxn];
int main()
{
	w[maxlen - 1] = pow(gen, (mod - 1) / (1 << maxlen - 1), mod);
	for(int i = maxlen - 2; i >= 0; --i)
		w[i] = (LL)w[i + 1] * w[i + 1] % mod;
	scanf("%d%s", &n, str);
	for(int i = 0; i < n; ++i)
		x[i] = str[n - 1 - i] - '0';
	scanf("%s", str);
	for(int i = 0; i < n; ++i)
		y[i] = str[n - 1 - i] - '0';
	int len = 1;
	for( ; len <= n; len <<= 1);
	len <<= 1;
	Conv(x, y, len);
	n += n - 1;
	for(int i = 0; i < n; ++i)
		if(x[i] >= 10)
		{
			x[i + 1] += x[i] / 10;
			x[i] %= 10;
		}
	if(x[n])
		++n;
	for(int i = n - 1; i >= 0; --i)
		printf("%d", x[i]);
	putchar('\n');
	return 0;
}
