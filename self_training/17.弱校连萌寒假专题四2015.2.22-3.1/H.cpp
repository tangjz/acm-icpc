#include <cstdio>
#include <cstring>
const int maxs = 60;
int n, k, m;
struct Matrix
{
	int r, c, num[maxs][maxs];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					tmp.num[i][k] = (tmp.num[i][k] + num[i][j] * x.num[j][k]) % m;
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
	while(scanf("%d%d%d", &n, &k, &m) == 3)
	{
		memset(&A, 0, sizeof A);
		A.r = A.c = n << 1;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				scanf("%d", &A.num[i][j]);
				A.num[i][n + j] = A.num[i][j] %= m;
			}
		for(int i = 0; i < n; ++i)
			A.num[n + i][n + i] = 1 % m;
		A = A.pow(k);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				printf("%d%c", A.num[i][n + j], " \n"[j == n - 1]);
	}
	return 0;
}
