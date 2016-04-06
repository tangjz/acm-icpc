#include <cstdio>
typedef long long LL;
const int maxm = 1 << 10, maxn = 1 << 7, mod = 19921107;
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
	Matrix pow(int k) const
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
int p, q, n, seq[maxn], ans;
bool vis[maxm];
int main()
{
	scanf("%d%d", &p, &q);
	for(int i = 0, j = 1 << p; i < j; ++i)
	{
		vis[i] = vis[i >> 1] || ((i & 3) == 3);
		if(!vis[i] && !(p > 1 && (i & (1 << p - 1)) && (i & 1)))
			seq[n++] = i;
	}
	A.r = A.c = n;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			A.num[i][j] = !(seq[i] & seq[j]);
	if(q == 1)
		ans = n;
	else
	{
		A = A.pow(q - 1);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(!(seq[i] & seq[j]))
				{
					ans += A.num[i][j];
					if(ans >= mod)
						ans -= mod;
				}
	}
	printf("%d\n", ans);
	return 0;
}
