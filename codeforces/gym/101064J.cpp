#include <cstdio>
typedef long double DB;
const int maxk = 5, maxs = 1 << 12 | 1, maxs2 = 15625;
const DB eps = 1e-10;
inline int sgn(DB x)
{
	return (x > eps) - (x < -eps);
}
int s[maxs], p[maxk][maxs];
DB f[maxk][maxs], g[maxs2];
int main()
{
	for(int i = 0; i < 1 << 12; ++i)
	{
		int cnt[5] = {};
		for(int j = 0; j < 6; ++j)
		{
			int msk = (i >> (j << 1)) & 3;
			++cnt[msk];
			if(msk && cnt[msk] == 3)
				s[i] += msk;
			if(msk && cnt[msk] > 3)
				++s[i];
		}
		f[0][i] = s[i];
	}
	for(int i = 1; i < maxk; ++i)
	{
		for(int j = 0; j < maxs2; ++j)
			g[j] = 0;
		for(int j = 0; j < 1 << 12; ++j)
		{
			int jj = 0;
			for(int o = 5; o >= 0; --o)
				jj = jj * 5 + ((j >> (o << 1)) & 3);
			g[jj] = f[i - 1][j];
		}
		for(int j = 0, pw = 1; j < 6; ++j, pw *= 5)
			for(int k = 0; k < maxs2; ++k)
				if((k / pw) % 5 == 4)
					for(int o = 1; o <= 4; ++o)
						g[k] += g[k - o * pw] * (o == 4 ? 1.0 / 2 : 1.0 / 6);
		for(int j = 0; j < 1 << 12; ++j)
		{
			f[i][j] = -1e10;
			for(int k = 0; k < 1 << 6; ++k)
			{
				int jj = 0;
				for(int o = 5; o >= 0; --o)
					if((k >> o) & 1)
						jj = jj * 5 + ((j >> (o << 1)) & 3);
					else
						jj = jj * 5 + 4;
				if(sgn(f[i][j] - g[jj]) < 0)
				{
					p[i][j] = jj;
					f[i][j] = g[jj];
				}
			}
		}
	}
	int t, m;
	char buf[7];
	scanf("%d", &t);
	while(t--)
	{
		int msk = 0;
		scanf("%d%s", &m, buf);
		for(int i = 0; i < 6; ++i)
			msk |= (buf[i] >= '1' && buf[i] <= '3' ? buf[i] - '0' : 0) << (i << 1);
		printf("%.10f\n", (double)f[m][msk]);
		if(!m)
			puts("-");
		else
		{
            bool empty = 1;
			int pmsk = p[m][msk];
			for(int i = 0; i < 6; ++i, pmsk /= 5)
				if(pmsk % 5 == 4) {
                    empty = 0;
					putchar(buf[i]);
                }
            if(empty)
                putchar('-');
			putchar('\n');
		}
	}
	return 0;
}
