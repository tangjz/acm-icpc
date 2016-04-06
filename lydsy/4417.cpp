#include <cstdio>
const int maxn = 101, mod = 30011;
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
					ret.num[i][k] = (ret.num[i][k] + num[i][j] * t.num[j][k]) % mod;
		return ret;
	}
	Matrix pow(int k)
	{
		Matrix ret = {}, tmp = *this;
		ret.r = ret.c = r;
		for(int i = 0; i < r; ++i)
			++ret.num[i][i];
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
	int n, m;
	scanf("%d%d", &n, &m);
	if(m == 2)
	{
		puts(n <= 2 ? "1" : "0");
		return 0;
	}
	A.r = A.c = n << 1;
	for(int i = 0; i < n; ++i)
	{
		++A.num[i + n][i];
		++A.num[i][i + n];
		if(i)
			++A.num[i - 1 + n][i + n];
		++A.num[i + n][i + n];
		if(i + 1 < n)
			++A.num[i + 1 + n][i + n];
	}
	A = A.pow(m - 3);
	int pos = (n << 1) - 1, ans = A.num[0][pos] + A.num[n][pos];
	if(n > 1)
	{
		ans += A.num[1][pos] + A.num[n][pos] + (A.num[n + 1][pos] << 1);
		if(n > 2)
			ans += A.num[n + 2][pos];
	}
	printf("%d\n", ans % mod);
	return 0;
}
