#include <stdio.h>
typedef long long LL;
const int maxn = 1010;
int mod;
struct Matrix
{
	int r, c, num[2][maxn];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = (Matrix){r, t.c};
		if(r == 1)
		{
			for(int i = 0; i < t.c; ++i)
				for(int j = 0; j <= i; ++j)
					ret.num[0][i] = (ret.num[0][i] + (LL)num[0][j] * t.num[0][i - j]) % mod;
		}
		else
		{
			for(int i = 0; i < t.c; ++i)
			{
				ret.num[0][i] = (ret.num[0][i] + (LL)num[0][0] * t.num[0][i]) % mod;
				for(int j = 1; j <= i; ++j)
					ret.num[0][i] = (ret.num[0][i] + (LL)num[0][j] * t.num[1][i + 1 - j]) % mod;
			}
			for(int i = 1; i < t.c; ++i)
				for(int j = 1; j <= i; ++j)
					ret.num[1][i] = (ret.num[1][i] + (LL)num[1][j] * t.num[1][i + 1 - j]) % mod;
		}
		return ret;
	}
	Matrix pow(LL k) const
	{
		Matrix ret = (Matrix){r, c}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A, B;
int n, L, R, b, f[maxn], g[maxn], ans;
int main()
{
	scanf("%d%d%d%d%d", &n, &L, &R, &b, &mod);
	b %= mod;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", f + i);
		f[i] %= mod;
	}
	for(int i = 1; i < n; ++i)
		for(int j = n - 1; j >= i; --j)
		{
			f[j] -= f[j - 1];
			if(f[j] < 0)
				f[j] += mod;
		}
	if(L < 0)
	{
		A = (Matrix){1, n};
		for(int i = 0; i < n; ++i)
			A.num[0][i] = i & 1 ? -1 : 1;
		A = A.pow(-L);
	}
	else
		A = (Matrix){1, n, 1, n > 1}.pow(L);
	for(int i = 0; i < n; ++i)
		for(int j = i; j < n; ++j)
			g[i] = (g[i] + (LL)A.num[0][j - i] * f[j]) % mod;
	A = (Matrix){2, n + 1, b, b};
	A.num[1][1] = 1;
	A.num[1][2] = n > 1;
	A = A.pow((LL)R - L + 1);
	for(int i = 0; i < n; ++i)
		ans = (ans + (LL)A.num[0][i + 1] * g[i]) % mod;
	printf("%d\n", ans);
	return 0;
}
