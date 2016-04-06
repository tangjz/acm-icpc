#include <stdio.h>
const int maxn = 4, mod = 1000000007;
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
} A, B;
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
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
		case 2 : A = (Matrix){1, 2, 1, 1}; B = (Matrix){2, 2, 0, 1, 0, 0, 1, 1}; break;
		case 3 : A = (Matrix){1, 2, 1, 1}; B = (Matrix){2, 2, 0, mod - 1, 0, 0, 1, 4}; break;
		case 4 : A = (Matrix){1, 4, 1, 0, 1, 1}; B = (Matrix){4, 4, 0, 0, 0, mod - 1, 1, 0, 0, 1, 0, 1, 0, 5, 0, 0, 1, 1}; break;
		case 5 : A = (Matrix){1, 4, 95, 8, 1, 1}; B = (Matrix){4, 4, 0, 0, 0, mod - 1, 1, 0, 0, 15, 0, 1, 0, mod - 32, 0, 0, 1, 15}; break;
	}
	A = A * B.pow((n & 1) ? (m >> 1) : (m - 1));
	printf("%d\n", A.num[0][A.c - 1]);
	return 0;
}
