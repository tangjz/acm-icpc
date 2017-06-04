#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 19, maxd = 10, maxm = 1 << (maxd - 1) | 1;
LL f[maxn][maxn][maxm];
LL solve(LL lim, int tim)
{
	LL ret = 0;
	static char dig[maxn];
	int len = sprintf(dig, "%lld", lim), msk = 0;
	std::reverse(dig, dig + len);
	for(int i = len - 1; i >= 0; --i)
	{
		int x = dig[i] - '0';
		for(int y = 0; y < x; ++y)
		{
			int tim2 = tim, msk2 = msk & ((1 << y) - 1);
			if(y && !((msk2 >> (y - 1)) & 1))
			{
				--tim2;
				msk2 |= 1 << (y - 1);
			}
			if(tim2 >= 0)
				ret += f[i][tim2][msk2];
		}
		msk &= (1 << x) - 1;
		if(x && !((msk >> (x - 1)) & 1))
		{
			--tim;
			msk |= 1 << (x - 1);
		}
	}
	return ret;
}
int main()
{
	for(int i = 0; i < 1 << (maxd - 1); ++i)
		f[0][0][i] = 1;
	for(int i = 1; i < maxn; ++i)
		for(int j = 0; j < maxn; ++j)
			for(int k = 0; k < 1 << (maxd - 1); ++k)
				for(int o = 0; o < maxd; ++o)
				{
					int jj = j, kk = k & ((1 << o) - 1);
					if(o && !((kk >> (o - 1)) & 1))
					{
						--jj;
						kk |= 1 << (o - 1);
					}
					if(jj >= 0)
						f[i][j][k] += f[i - 1][jj][kk];
				}
	int t, k;
	LL L, R;
	t = 1; // scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld%d", &L, &R, &k);
		printf("%lld\n", solve(R + 1, k) - solve(L, k));
	}
	return 0;
}
