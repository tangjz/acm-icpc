#include <cstdio>
const int maxn = 100, maxt = 131072, maxs = 128;
int a[maxt + maxn + 10][2], h[maxt + maxn + 10][2], f[maxn + 10][maxn + 10];
void scan(int &x)
{
    int ch;
    while((ch = getchar()) < '0' || ch > '9');
    x = ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	for(int d = 0; d < 2; ++d)
		for(int i = 2; i <= maxt + maxn; ++i)
		{
			scan(a[i][d]);
			h[i][d] = (i >= maxs ? h[i - maxs][d] : 0) ^ a[i][d];
		}
	for(int i = 2; i <= maxn; ++i)
	{
		f[1][i] = a[i + maxt][0] ^ a[i][0];
		f[i][1] = a[i + maxt][1] ^ a[i][1];
		int rev = ~(i - 2) & 127;
		for(int j = rev; ; j = (j - 1) & rev)
		{
			int res = i - 1 - ((i - 2) | j);
			if(res < 0)
				res += maxs;
			int L = i / maxs * maxs + res, R = (1 + maxt) / maxs * maxs + res;
			if(L < i)
				L += maxs;
			if(R > 1 + maxt)
				R -= maxs;
			f[1][i] ^= h[R][1] ^ (L >= maxs ? h[L - maxs][1] : 0);
			f[i][1] ^= h[R][0] ^ (L >= maxs ? h[L - maxs][0] : 0);
			if(!j)
				break;
		}
	}
	for(int i = 2; i <= maxn; ++i)
		for(int j = 2; j <= maxn; ++j)
			f[i][j] = f[i - 1][j] ^ f[i][j - 1];
	int q;
	scan(q);
	while(q--)
	{
		int n, m;
		scan(n), scan(m);
		printf("%d\n", f[n][m]);
	}
	return 0;
}
