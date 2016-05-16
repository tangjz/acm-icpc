#include <cstdio>
typedef long long LL;
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
					ret.num[i][k] = (ret.num[i][k] + num[i][j] * t.num[j][k]) & 3;
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
} A;
int t;
LL x, a, b, n;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld", &x, &a, &b, &n);
		bool flag = 1;
		LL lim = 10, val = x;
		flag &= b <= lim && val <= lim;
		for(int i = 1; i <= n && flag; ++i, val = val * a + b)
			flag &= val <= (lim - b) / a;
		if(flag)
		{
			puts(val == 5 || val == 9 ? "=" : "<");
			continue;
		}
		A = (Matrix){2, 2, (int)(a & 3), 0, (int)(b & 3), 1}.pow(n);
		val = (x * A.num[0][0] + A.num[1][0]) & 3;
		puts(val == 1 ? "=" : (val == 3 ? ">" : "<"));
	}
	return 0;
}
