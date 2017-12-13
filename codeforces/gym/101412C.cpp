#include <cstdio>
const int maxn = 50;
int n, m, p, x, y, z;
struct Matrix
{
	int r, c, num[maxn][maxn];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][j] = (ret.num[i][j] + num[i][k] * t.num[k][j]) % p;
		return ret;
	}
	Matrix pow(int k)
	{
		Matrix ret = {r, r}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} A, B;
int main()
{
	while(scanf("%d%d%d%d%d%d", &n, &p, &x, &y, &z, &m) == 6 && n + p + x + y + z + m)
	{
		A = (Matrix){1, n};
		for(int i = 0; i < n; ++i)
			scanf("%d", A.num[0] + i);
		B = (Matrix){n, n};
		for(int i = 0; i < n; ++i)
		{
			if(i)
				B.num[i][i - 1] = z;
			B.num[i][i] = y;
			if(i + 1 < n)
				B.num[i][i + 1] = x;
		}
		A = A * B.pow(m);
		for(int i = 0; i < n; ++i)
			printf("%d%c", A.num[0][i], " \n"[i == n - 1]);
	}
	return 0;
}
