#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxs = 4, mod = 1000000007;
int n, seq[maxs], ans;
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
int main()
{
	A = (Matrix){4, 4, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
	for(int i = 0; i < maxs; ++i)
		seq[i] = i;
	scanf("%d", &n);
	A = A.pow(n);
	do
	{
		int tmp = 1;
		for(int i = 0; i < maxs; ++i)
			tmp = (LL)tmp * A.num[i][seq[i]] % mod;
		ans += tmp;
		if(ans >= mod)
			ans -= mod;
	} while(next_permutation(seq, seq + maxs));
	printf("%d\n", ans);
	return 0;
}
