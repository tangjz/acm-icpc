#include <cstdio>
const int mod = 987654321;
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
struct Matrix
{
	int r, c, num[2][2];
	Matrix operator * (const Matrix &x) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					inc(ret.num[i][k], (long long)num[i][j] * x.num[j][k] % mod);
		return ret;
	}
	Matrix pow(unsigned int k)
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
	int p;
	A.r = A.c = 2;
	A.num[0][1] = A.num[1][0] = A.num[1][1] = 1;
	while(scanf("%d", &p) == 1 && p)
		if(p < 4 || p & 1)
			puts("0");
		else
			printf("%d\n", (A.pow(p - 4).num[1][1] - p / 2 + 1 + mod) % mod);
	return 0;
}
