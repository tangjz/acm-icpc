/*
 * 区间和即两部分前缀和相减，设前k项和为S_k
 * 构造向量[a_{i - k + 1}, a_{i - k + 2}, ..., a_{i}, S_i]的递推矩阵，快速幂即可
 */
#include <cstdio>
typedef long long LL;
int k, p;
struct Matrix
{
	int r, c, data[16][16];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r, tmp.c = c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					tmp.data[i][k] = (tmp.data[i][k] + (LL)data[i][j] * x.data[j][k]) % p;
		return tmp;
	}
} A, B;
int calc(LL n)
{
	if(n < k)
	{
		int ret = 0;
		for(int i = 0; i < n; ++i)
		{
			ret += A.data[0][i];
			if(ret >= p) ret -= p;
		}
		return ret;
	}
	n -= k;
	Matrix ans = A, tmp = B;
	while(n)
	{
		if(n & 1) ans = ans * tmp;
		tmp = tmp * tmp;
		n >>= 1;
	}
	return ans.data[0][k];
}
LL n, m;
int main()
{
	scanf("%d", &k);
	A.r = 1, A.c = B.r = B.c = k + 1;
	for(int i = 0; i < k; ++i)
		scanf("%d", &A.data[0][i]);
	for(int i = 1; i < k; ++i)
		B.data[i][i - 1] = 1;
	B.data[k][k] = 1;
	for(int i = k - 1; i >= 0; --i)
	{
		scanf("%d", &B.data[i][k - 1]);
		B.data[i][k] = B.data[i][k - 1];
	}
	scanf("%lld%lld%d", &m, &n, &p);
	for(int i = 0; i < k; ++i)
	{
		A.data[0][k] += A.data[0][i];
		if(A.data[0][k] >= p) A.data[0][k] -= p;
	}
	printf("%d\n", (calc(n) - calc(m - 1) + p) % p);
	return 0;
}
