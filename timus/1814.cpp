#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 3001, mod = 1000000007;
const double eps = 1e-8;
int n, m, len, dig[maxn];
struct Matrix
{
	int r, c, num[2][2];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = t.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * t.num[j][k]) % mod;
		return ret;
	}
	Matrix pow(int k)
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
int main()
{
	scanf("%d%d", &n, &m);
	++m;
	double res = sqrt(n);
	int p = (int)res, q = 1, r, tmp = 1;
	double first = res - p;
	do
	{
		tmp = q;
		q = n - p * p;
		r = __gcd(tmp, q);
		tmp /= r;
		q /= r;
		res = (sqrt(n) + p) * tmp / q;
		dig[len++] = (LL)res;
		p = abs(p - dig[len - 1] * q);
	} while(fabs(res - dig[len - 1] - first) >= eps);
	A = (Matrix){2, 2, 1, 0, 0, 1};
	for(int i = 0; i < len; ++i)
		A = A * (Matrix){2, 2, 0, 1, 1, dig[i]};
	A = A.pow(m / len);
	m %= len;
	for(int i = 0; i < m; ++i)
		A = A * (Matrix){2, 2, 0, 1, 1, dig[i]};
	p = A.num[1][0];
	q = A.num[0][0];
	tmp = q;
	q = p;
	p = ((LL)sqrt(n) * p + tmp) % mod;
	printf("%d/%d\n", p, q);
	return 0;
}