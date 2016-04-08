/*
 * æÿ’Ûº”ÀŸ 
 */
#include <cstdio>
#include <cstring>
long long m, a, c, x0, n, g;
long long Multiply(long long x, long long y)
{
	long long ans = 0;
	while(y)
	{
		if(y & 1) ans = (ans + x) % m;
		x = (x << 1) % m;
		y >>= 1;
	}
	return ans;
}
struct Matrix
{
	int r, c;
	long long num[2][2];
	Matrix(void) { r = c = 0; memset(num, 0, sizeof(num)); }
	Matrix operator * (const Matrix &x) const
	{
		Matrix temp;
		temp.r = r; temp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					temp.num[i][k] = (temp.num[i][k] + Multiply(num[i][j], x.num[j][k])) % m;
		return temp;
	}
	Matrix operator *= (const Matrix &x) { return *this = *this * x; }
} ans, sum;
int main()
{
	scanf("%lld%lld%lld%lld%lld%lld", &m, &a, &c, &x0, &n, &g);
	if(!n) printf("%lld\n", x0 % g);
	else
	{
		ans.r = 1; ans.c = 2; ans.num[0][0] = x0 % m; ans.num[0][1] = c % m;
		sum.r = 2; sum.c = 2; sum.num[0][0] = a % m; sum.num[1][0] = sum.num[1][1] = 1;
		while(n)
		{
			if(n & 1) ans *= sum;
			sum *= sum;
			n >>= 1;
		}
		printf("%lld\n", ans.num[0][0] % g);
	}
	return 0;
}
