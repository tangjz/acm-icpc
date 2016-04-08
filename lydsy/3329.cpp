#include <cstdio>
const int maxn = 61, mod = 1000000007;
struct Matrix
{
	int r, c, num[2][2];
	Matrix operator * (const Matrix &x) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < x.c; ++j)
			{
				long long tmp = 0;
				for(int k = 0; k < c; ++k)
					tmp += (long long)num[i][k] * x.num[k][j];
				ret.num[i][j] = tmp % mod;
			}
		return ret;
	}
	Matrix pow(long long k)
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
} A;
int t, sz, bit[maxn];
long long n, fib[maxn];
long long calc(long long n)
{
	long long ret = -1;
	++n;
	for(sz = 0; n; n >>= 1)
		bit[sz++] = n & 1;
	for(int i = sz - 1; i >= 0; --i)
		if(bit[i] == 1)
		{
			ret += fib[i + 1];
			if(i + 1 < sz && bit[i] == bit[i + 1])
				break;
		}
	return ret;
}
int main()
{
	fib[0] = fib[1] = 1;
	for(int i = 2; i < maxn; ++i)
		fib[i] = fib[i - 1] + fib[i - 2];
	A.r = A.c = 2;
	A.num[0][1] = A.num[1][0] = A.num[1][1] = 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		printf("%lld\n%d\n", calc(n), A.pow(n + 2).num[0][1]);
	}
	return 0;
}
