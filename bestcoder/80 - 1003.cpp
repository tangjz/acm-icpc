#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL n;
int t, a, b, c, p;
struct Matrix
{
	int row, col, num[3][3];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {};
		ret.row = row;
		ret.col = t.col;
		for(int i = 0; i < row; ++i)
			for(int j = 0; j < col; ++j)
				for(int k = 0; k < t.col; ++k)
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * t.num[j][k]) % (p - 1);
		return ret;
	}
	Matrix pow(LL k)
	{
		Matrix ret = {}, tmp = *this;
		ret.row = ret.col = row;
		for(int i = 0; i < row; ++i)
			ret.num[i][i] = 1 % (p - 1);
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
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%d%d%d%d", &n, &a, &b, &c, &p);
		if(a % p == 0 && n > 1)
		{
			puts("0");
			continue;
		}
		A.row = A.col = 3;
		A.num[0][0] = 0,			A.num[0][1] = 1 % (p - 1),	A.num[0][2] = 0;
		A.num[1][0] = 1 % (p - 1),	A.num[1][1] = c % (p - 1),	A.num[1][2] = 0;
		A.num[2][0] = 0,			A.num[2][1] = b % (p - 1),	A.num[2][2] = 1 % (p - 1);
		A = A.pow(n - 1);
		printf("%d\n", mod_pow(a, A.num[2][1]));
	}
	return 0;
}
