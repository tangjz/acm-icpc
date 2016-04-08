#include <cstdio>
int n, m;
struct Matrix
{
	int r, c, num[5][5];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < x.c; ++j)
			{
				long long sum = 0;
				for(int k = 0; k < c; ++k)
					sum += (long long)num[i][k] * x.num[k][j];
				tmp.num[i][j] = sum % m;
			}
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
int main()
{
	A.r = A.c = 5;
	A.num[0][0] = A.num[0][1] = A.num[0][2] = A.num[1][0] = A.num[2][0] = A.num[2][4] = A.num[3][0] = A.num[3][3] = A.num[4][2] = 1;
	A.num[0][3] = 2;
	while(scanf("%d%d", &n, &m) == 2 && n + m)
		printf("%d\n", A.pow(n).num[0][0]);
	return 0;
}