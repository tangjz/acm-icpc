#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001, maxs = 3, mod = 19940417;
int n, m, a[maxn], ans;
struct Matrix
{
	int r, c, num[maxs][maxs];
	Matrix operator * (const Matrix &x) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < x.c; ++j)
			{
				LL tmp = 0;
				for(int k = 0; k < c; ++k)
					tmp += (LL)num[i][k] * x.num[k][j];
				ret.num[i][j] = tmp % mod;
			}
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
} A, B, C;
int calc(int x, int d, int k)
{
	A = (Matrix){2, 2, 0, 1, 0, 1, 1, 0};
	B = A.pow(d);
	A = A.pow(x);
	C = (Matrix){1, 3, A.num[0][0], A.num[0][1], 0};
	B.r = B.c = 3;
	B = (Matrix){3, 3, B.num[0][0], B.num[0][1], 0, B.num[1][0], B.num[1][1], 1, 0, 0, 1};
	C = C * B.pow(k);
	return C.num[0][2];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	ans = calc(m, 0, 1);
	for(int i = 0, last = 0, tmp; i < n && a[i] < m; ++i)
	{
		if(last != a[i])
		{
			last = a[i];
			tmp = calc(m % a[i], a[i], m / a[i]);
		}
		ans += tmp;
		if(ans >= mod)
			ans -= mod;
	}
	printf("%d\n", ans);
	return 0;
}
