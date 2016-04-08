#include <cstdio>
typedef long long LL;
LL n, m, p;
void inc(LL &x, LL y)
{
	x += y;
	if(x >= p)
		x -= p;
}
void dec(LL &x, LL y)
{
	x -= y;
	if(x < 0)
		x += p;
}
LL mul(LL x, LL y)
{
	LL ret = 0;
	while(y)
	{
		if(y & 1)
			inc(ret, x);
		inc(x, x);
		y >>= 1;
	}
	return ret;
}
struct Matrix
{
	int r, c;
	LL num[2][2];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					inc(tmp.num[i][k], mul(num[i][j], x.num[j][k]));
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
LL solve(LL n, LL m)
{
	LL ret = 0;
	if((n / m) & 1)
	{
		inc(ret, A.pow(m - n % m).num[0][1]);
		if(~(n % m) & 1)
		{
			if(ret)
				ret = p - ret;
			inc(ret, A.pow(m).num[0][1]);
		}
	}
	else
		inc(ret, A.pow(n % m).num[0][1]);
	if((m & 1) && ((n / m >> 1) & 1))
	{
		if(ret)
			ret = p - ret;
		inc(ret, A.pow(m).num[0][1]);
	}
	return ret;
}
int main()
{
	A.r = A.c = 2;
	A.num[0][1] = A.num[1][0] = A.num[1][1] = 1;
	scanf("%I64d%I64d%I64d", &n, &m, &p);
	if(p == 1)
	{
		puts("0");
		return 0;
	}
	LL ret = solve(n + 2, m);
	dec(ret, 1);
	if((n + 2) % m == 0)
		inc(ret, A.pow(m).num[0][1]);
	printf("%I64d\n", ret);
	return 0;
}
