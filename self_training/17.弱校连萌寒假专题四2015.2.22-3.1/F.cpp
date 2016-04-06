#include <cstdio>
const int mod = 10000;
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
					tmp.num[i][k] = (tmp.num[i][k] + num[i][j] * x.num[j][k]) % mod;
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
} A;
int n;
int main()
{
	A.r = A.c = 2;
	A.num[0][1] = A.num[1][0] = A.num[1][1] = 1;
	while(scanf("%d", &n) != EOF && n != -1)
		printf("%d\n", A.pow(n + 1).num[0][0]);
	return 0;
}
