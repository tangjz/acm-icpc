#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100, maxm = 10, mod = 1000000009;
int m, c[maxm];
LL n;
struct Matrix
{
	int r, c, num[maxn][maxn];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = t.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < t.c; ++j)
			{
				LL tmp = 0;
				for(int k = 0; k < c; ++k)
					tmp += (LL)num[i][k] * t.num[k][j];
				ret.num[i][j] = tmp % mod;
			}
		return ret;
	}
	Matrix pow(LL k)
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
inline int idx(int i, int j)
{
	return i * (m + 1) + j;
}
inline void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	while(scanf("%lld%d", &n, &m) == 2)
	{
		for(int i = 1; i <= m; ++i)
			scanf("%d", c + i);
		for( ; m > 1 && !c[m]; --m);
		A.r = A.c = m * (m + 1);
		memset(A.num, 0, sizeof A.num);
		for(int i = 1; i <= m; ++i)
			for(int j = 1; j <= m; ++j)
			{
				inc(A.num[idx(m - min(i, j), i)][idx(m - 1, abs(i - j))], c[j]);
				if(i == j)
					for(int k = 1; k <= m; ++k)
						inc(A.num[idx(m - i, i)][idx(m - 1, k)], (LL)c[j] * c[k] % mod);
			}
		inc(A.num[idx(m - 1, 0)][idx(m - 1, 0)], c[2]);
		for(int k = 1; k <= m; ++k)
			inc(A.num[idx(m - 1, 0)][idx(m - 1, k)], (LL)c[2] * c[k] % mod);
		for(int i = 1; i < m; ++i)
			for(int j = 0; j <= m; ++j)
				inc(A.num[idx(m - i, j)][idx(m - i - 1, j)], 1);
		A = A.pow(n);
		B.r = 1, B.c = m * (m + 1);
		memset(B.num, 0, sizeof B.num);
		B.num[0][idx(m - 1, 0)] = 1;
		for(int i = 1; i <= m; ++i)
			inc(B.num[0][idx(m - 1, i)], (LL)B.num[0][idx(m - 1, 0)] * c[i] % mod);
		B = B * A;
		printf("%d\n", B.num[0][idx(m - 1, 0)]);
	}
	return 0;
}
