#include <cstdio>
const int maxn = 100010, mod = 23333333;
int n, f[maxn];
inline void mod_inc(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
inline void mod_dec(int &x, int y)
{
	if((x -= y) < 0)
		x += mod;
}
int main()
{
	scanf("%d", &n);
	f[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j * (3 * j - 1) >> 1 <= i; ++j)
			if(j & 1)
				mod_inc(f[i], f[i - (j * (3 * j - 1) >> 1)]);
			else
				mod_dec(f[i], f[i - (j * (3 * j - 1) >> 1)]);
		for(int j = 1; j * (3 * j + 1) >> 1 <= i; ++j)
			if(j & 1)
				mod_inc(f[i], f[i - (j * (3 * j + 1) >> 1)]);
			else
				mod_dec(f[i], f[i - (j * (3 * j + 1) >> 1)]);
	}
	for(int i = 1; i * (i + 1) <= n; ++i)
		for(int j = n; j >= i * (i + 1); --j)
			mod_dec(f[j], f[j - i * (i + 1)]);
	printf("%d\n", f[n]);
	return 0;
}
