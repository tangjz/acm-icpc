#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 1000001, maxs = 28, mod = 1000000009;
int t, n, len[3], f[maxn][4], g[maxs][maxs][maxs][4][4];
char str[3][maxn];
int main()
{
	for(int i = 0; i < maxs; ++i)
	{
		int iL, iR;
		i == maxs - 1 ? iL = 1, iR = maxs - 2 : iL = iR = i;
		for(int j = 0; j < maxs; ++j)
		{
			int jL, jR;
			j == maxs - 1 ? jL = 1, jR = maxs - 2 : jL = jR = j;
			for(int k = 0; k < maxs; ++k)
			{
				int kL, kR;
				k == maxs - 1 ? kL = 1, kR = maxs - 2 : kL = kR = k;
				for(int ii = iL; ii <= iR; ++ii)
					for(int jj = jL; jj <= jR; ++jj)
						for(int kk = kL; kk <= kR; ++kk)
						{
							if(ii == jj && jj == kk)
								++g[i][j][k][0][0];
							if(ii == jj && jj < kk)
								++g[i][j][k][0][1];
							if(ii < jj && jj == kk)
								++g[i][j][k][0][2];
							if(ii < jj && jj < kk)
								++g[i][j][k][0][3];
							if(ii == jj)
								++g[i][j][k][1][1];
							if(ii < jj)
								++g[i][j][k][1][3];
							if(jj == kk)
								++g[i][j][k][2][2];
							if(jj < kk)
								++g[i][j][k][2][3];
							++g[i][j][k][3][3];
						}
			}
		}
	}
	f[0][0] = 1;
	scanf("%d", &t);
	while(t--)
	{
		n = 0;
		for(int i = 0; i < 3; ++i)
		{
			scanf("%s", str[i]);
			len[i] = strlen(str[i]);
			if(n < len[i])
				n = len[i];
		}
		memset(f + 1, 0, n * sizeof f[0]);
		for(int i = 1; i <= n; ++i)
		{
			int ch[3];
			for(int j = 0; j < 3; ++j)
				ch[j] = i <= len[j] ? (str[j][i - 1] == '?' ? maxs - 1 : str[j][i - 1] - 'a' + 1) : 0;
			int (*h)[4] = g[ch[0]][ch[1]][ch[2]];
			for(int j = 0; j < 4; ++j)
				if(f[i - 1][j])
					for(int k = 0; k < 4; ++k)
						if(h[j][k])
							f[i][k] = (f[i][k] + (LL)f[i - 1][j] * h[j][k]) % mod;
		}
		printf("%d\n", f[n][3]);
	}
	return 0;
}
