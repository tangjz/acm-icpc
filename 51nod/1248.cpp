#include <stdio.h>
typedef long long LL;
const int mod = 1000000007;
inline int mod_add(int x, int y)
{
	return x + y < mod ? x + y : x + y - mod;
}
struct Matrix
{
	int r, c, num[2][2];
	Matrix operator + (const Matrix &t) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				ret.num[i][j] = mod_add(num[i][j], t.num[i][j]);
		return ret;
	}
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = t.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = mod_add(ret.num[i][k], (LL)num[i][j] * t.num[j][k] % mod);
		return ret;
	}
	Matrix pow(LL k) const
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
} A, B, C;
int main()
{
	int n;
	scanf("%d", &n);
	A = (Matrix){1, 2, 1, 3};
	while(n--)
	{
		LL x;
		scanf("%lld", &x);
		B = (Matrix){2, 2, 0, mod - 1, 1, 6}.pow(x);
		B = B + (Matrix){2, 2, B.num[1][1], B.num[1][0], B.num[0][1], B.num[0][0]};
		A = A * B;
	}
	printf("%d\n", A.num[0][0]);
	return 0;
}
