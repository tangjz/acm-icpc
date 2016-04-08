/*
 * fib_0 = 0, fib_1 = 1, fib_i = fib_{i - 1} + fib_{i - 2}
 * Éè´ð°¸ÎªS_n
 * S_n = \sum_{i = 1}^n{fib_i * S_{n - i}}
 * = fib_1 * S_{n - 1} + \sum_{i = 2}^n{fib_i * S_{n - i}}
 * = S_{n - 1} + \sum_{i = 2}^n{fib_{i - 1} * S_{n - i}} + \sum_{i = 2}^n{fib_{i - 2} * S_{n - i}}
 * = S_{n - 1} + \sum_{i = 1}^{n - 1}{fib_i * S_{n - 1 - i}} + \sum_{i = 0}^{n - 2}{fib_i * S_{n - 2 - i}}
 * = S_{n - 1} + S_{n - 1} + S_{n - 2}
 * = 2 * S_{n - 1} + S_{n - 2}
 */
#include <cstdio>
typedef long long LL;
const int mod = 1000000007;
struct Matrix
{
	int r, c, data[2][2];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r, tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
			{
				LL sum = 0;
				for(int k = 0; k < x.c; ++k)
					sum += data[i][k] * (LL)x.data[k][j];
				tmp.data[i][j] = sum % mod;
			}
		return tmp;
	}
} A, B;
int n;
int main()
{
	scanf("%d", &n); --n;
	A.r = A.data[0][1] = B.data[0][1] = B.data[1][0] = 1;
	A.c = B.r = B.c = B.data[1][1] = 2;
	while(n)
	{
		if(n & 1) A = A * B;
		B = B * B;
		n >>= 1;
	}
	printf("%d\n", A.data[0][1]);
	return 0;
}
