#include <cstdio>
const int maxn = 4, mod = 1000000000;
typedef long long LL;
struct Matrix
{
	int r, c, num[maxn][maxn];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = t.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * t.num[j][k]) % mod;
		return ret;
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
	int m, n;
	scanf("%d%d", &m, &n);
	if((n & 1) && (m & 1))
	{
		puts("0");
		return 0;
	}
	if(m < n)
	{
		m = n + m;
		n = m - n;
		m = m - n;
	}
	switch(n)
	{
		case 2 : A = (Matrix){1, 1, 1}; break;
		case 3 : A = (Matrix){1, 1, 2}; break;
		case 4 : A = (Matrix){4, 4, 0, 0, 0, 1, 1, 0, 0, mod - 2, 0, 1, 0, 2, 0, 0, 1, 2}; break;
		case 5 : A = (Matrix){3, 3, 0, 0, 2, 0, 1, 0, 0, 0, 0, 1, 11, 0}; break;
	}
	if(n <= 4)
		printf("%d\n", (A.pow(m - 2 >> (n & 1)).num[A.r - 1][A.c - 1] << 1) % mod);
	else // n = 5 m >= 6
	{
		A = A.pow(m - 4 >> 1);
		printf("%d\n", (2LL * A.num[1][2] + 28LL * A.num[2][2]) % mod);
	}
	return 0;
}
