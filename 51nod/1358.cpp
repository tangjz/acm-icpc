#include <cstdio>
const int maxn = 35, mod = 1000000007;
typedef long long LL;
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
struct Matrix
{
	int r, c, num[maxn][maxn];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < c; ++k)
					inc(tmp.num[i][k], (LL)num[i][j] * x.num[j][k] % mod);
		return tmp;
	}
	Matrix pow(int k)
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
LL n;
int main()
{
	scanf("%lld", &n);
	if(n <= 4)
	{
		puts("1");
		return 0;
	}
	n = (n - 4) * 10;
	A.r = 1;
	A.c = B.r = B.c = 34;
	for(int i = 0; i < A.c; ++i)
		A.num[0][i] = 1;
	B.num[9][0] = B.num[33][0] = 1;
	for(int i = 1; i < B.r; ++i)
		B.num[i - 1][i] = 1;
	printf("%d\n", (A * B.pow(n)).num[0][0]);
	return 0;
}
