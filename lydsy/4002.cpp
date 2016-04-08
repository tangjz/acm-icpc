#include <cstdio>
#include <cstring>
typedef unsigned long long ULL;
const ULL XiuEnAi = 7528443412579576937ULL;
void inc(ULL &x, ULL y)
{
	x += y;
	if(x >= XiuEnAi)
		x -= XiuEnAi;
}
ULL Mul(ULL x, ULL y)
{
	ULL ret = 0;
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
	ULL num[2][2];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					inc(tmp.num[i][k], Mul(num[i][j], x.num[j][k]));
		return tmp;
	}
} A, B;
ULL b, d, n, nn;
int main()
{
	scanf("%llu%llu%llu", &b, &d, &n);
	nn = n;
	A = (Matrix){1, 2, 2ULL, b};
	B = (Matrix){2, 2, 0LL, d - b * b >> 2, 1LL, b};
	while(n)
	{
		if(n & 1)
			A = A * B;
		B = B * B;
		n >>= 1;
	}
	if(d != b * b && (~nn & 1))
	{
		--A.num[0][0];
		if(A.num[0][0] < 0)
			A.num[0][0] += XiuEnAi;
	}
	printf("%llu\n", A.num[0][0]);
	return 0;
}
