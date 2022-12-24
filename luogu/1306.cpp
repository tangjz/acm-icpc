#include <cstdio>
const long long mod = 100000000;
inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int n, m;
struct Matrix
{
	int r, c; long long num[2][2];
	Matrix(void) { r = c = 0; num[0][0] = num[0][1] = num[1][0] = num[1][1] = 0; }
	Matrix operator * (const Matrix &x) const
	{
		Matrix temp;
		temp.r = r; temp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k) temp.num[i][k] = (temp.num[i][k] + num[i][j] * x.num[j][k]) % mod;
		return temp;
	}
	Matrix operator *= (const Matrix &x) { return *this = *this * x; }
} ans, sum;
int main()
{
	scanf("%d%d", &n, &m);
	n = gcd(n, m);
	if(n <= 2) puts("1");
	else
	{
		n -= 2;
    	ans.r = 1, ans.c = 2, ans.num[0][0] = ans.num[0][1] = 1;
		sum.r = sum.c = 2, sum.num[0][1] = sum.num[1][0] = sum.num[1][1] = 1;
		while(n)
		{
			if(n & 1) ans *= sum;
			sum *= sum;
			n >>= 1;
		}
		printf("%I64d\n", ans.num[0][1]);
	}
}