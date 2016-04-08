#include <cstdio>
const int maxn = 2, mod = 1000000007;
typedef long long LL;
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
					inc(tmp.num[i][k], (LL)num[i][j] * x.num[j][k] % mod);
		return tmp;
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
int t;
LL n, m;
int solve(LL n, LL m)
{
	int ret = 0;
	if((n / m) & 1)
	{
		inc(ret, A.pow(m - n % m).num[0][1]);
		if(~(n % m) & 1)
		{
			if(ret)
				ret = mod - ret;
			inc(ret, A.pow(m).num[0][1]);
		}
	}
	else
		inc(ret, A.pow(n % m).num[0][1]);
	if((m & 1) && ((n / m >> 1) & 1))
	{
		if(ret)
			ret = mod - ret;
		inc(ret, A.pow(m).num[0][1]);
	}
	return ret;
}
int main()
{
	A.r = A.c = 2;
	A.num[0][1] = A.num[1][0] = A.num[1][1] = 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &n, &m);
		printf("%d\n", solve(n, m));
	}
	return 0;
}
