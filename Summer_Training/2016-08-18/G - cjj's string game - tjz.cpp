#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 11, mod = 1000000007;
struct Matrix
{
	int r, c, num[maxn][maxn];
	void init(int _r, int _c)
	{
		r = _r;
		c = _c;
		for(int i = 0; i < r; ++i)
			memset(num[i], 0, c * sizeof(int));
	}
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * t.num[j][k]) % mod;
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
int t, n, m, p;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &p);
		A.init(m + 1, m + 1); // <= m
		B.init(m, m); // < m
		for(int i = 0; i <= m; ++i)
		{
			A.num[i][0] = p * (p - 1);
			if(i + 1 <= m)
				A.num[i][i + 1] = p;
			if(i < m)
			{
				B.num[i][0] = p * (p - 1);
				if(i + 1 < m)
					B.num[i][i + 1] = p;
			}
		}
		A = A.pow(n);
		B = B.pow(n);
		int ans = 0;
		for(int i = 0; i <= m; ++i)
		{
			if((ans += A.num[0][i]) >= mod)
				ans -= mod;
			if(i < m && (ans -= B.num[0][i]) < 0)
				ans += mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
