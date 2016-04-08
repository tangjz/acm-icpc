/*
 * KMP预处理出递推矩阵 然后加速 
 */
#include<cstdio>
int n, m, K, a[30], p[30];
struct Matrix
{
	int r, c, num[30][30];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r, tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k) tmp.num[i][k] = (tmp.num[i][k] + num[i][j] * x.num[j][k]) % K;
		return tmp;
	}
	Matrix operator *= (const Matrix &x) { return *this = *this * x; }
} dp = {}, z = {};
Matrix pow(Matrix x, int N)
{
	Matrix res = {};
	res.r = res.c = x.r; for(int i = 0; i < x.r; ++i) res.num[i][i] = 1;
	while(N)
	{
		if(N & 1) res *= x;
		x *= x;
		N >>= 1;
	}
	return res;
}
int main()
{
	int i, j, k, t, ans;
	char ch;
	scanf("%d%d%d", &n, &m, &K);
	for(i = 1; i <= m; ++i)
	{
		while((ch = getchar()) < '0' || ch > '9');
		a[i]  = ch - '0';
	}
	p[1] = 0; j = 0;
	for(i = 2; i <= m; ++i)
	{
		while(j > 0 && a[j + 1] != a[i]) j = p[j];
		if(a[j + 1] == a[i]) ++j;
		p[i] = j;
	}
	z.r = m, z.c = 1, z.num[0][0] = 1;
	dp.r = dp.c = m;
	for(j = 0; j < m; ++j)
		for(k = 0; k < 10; ++k)
		{
			t = j;
			while(t > 0 && a[t + 1] != k) t = p[t];
			if(a[t + 1] == k) ++t;
			if(t != m) dp.num[t][j] = (dp.num[t][j] + 1) % K;
	}
	z = pow(dp, n) * z;
	ans = 0;
	for(i = 0; i < m; ++i) ans = (ans + z.num[i][0]) % K;
	printf("%d\n", ans);
	return 0;
}
