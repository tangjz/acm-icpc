#include <cstdio>
typedef __int128 LLL;
typedef long long LL;
int t, p;
LL n;
int inv(int x)
{
	return x <= 1 ? x : p - p / x * (LL)inv(p % x) % p;
}
LL mod_pow(LL x, LL k, LL p)
{
	LL ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LLL)ret * x % p;
		x = (LLL)x * x % p;
		k >>= 1;
	}
	return ret;
}
struct Matrix
{
	int r, c, num[2][2];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					tmp.num[i][k] = (tmp.num[i][k] + (LL)num[i][j] * x.num[j][k]) % p;
		return tmp;
	}
	Matrix pow(LL k)
	{
		Matrix ret = {}, tmp = *this;
		ret.r = ret.c = r;
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
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%d", &n, &p);
		if(p <= 3)
		{
			puts("1");
			continue;
		}
		A = (Matrix){2, 2, 0, p - 1, 1, 11 % p};
		n = mod_pow(2, n - 1, (LL)p * p - 1);
		B = A.pow(n);
		int ans = (2LL * B.num[0][0] + 11LL * B.num[1][0] - 5) % p;
		if(ans < 0)
			ans += p;
		ans = (LL)ans * inv(6 % p) % p;
		printf("%d\n", ans);
	}
	return 0;
}
