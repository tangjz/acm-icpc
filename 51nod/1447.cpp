#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 20, maxm = 26;
int n, m, c[maxn][maxm], f[1 << maxn], g[maxn][maxm], h[maxn][maxm];
char str[maxn][maxm];
inline void upd(int &x, int y)
{
    if(x > y)
        x = y;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", str[i]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", c[i] + j);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
		{
			int mx = 0;
			for(int k = 0; k < n; ++k)
				if(str[i][j] == str[k][j])
				{
					g[i][j] |= 1 << k;
					h[i][j] += c[k][j];
					if(mx < c[k][j])
						mx = c[k][j];
				}
			h[i][j] -= mx;
		}
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int i = 1; i < 1 << n; ++i)
	{
		int lbt = -1;
		for(int j = 0; j < n; ++j)
			if((i >> j) & 1)
			{
				lbt = j;
				break;
			}
		for(int j = 0; j < m; ++j)
		{
			upd(f[i], f[i ^ (1 << lbt)] + c[lbt][j]);
			upd(f[i], f[i & (~g[lbt][j])] + h[lbt][j]);
		}
	}
	printf("%d\n", f[(1 << n) - 1]);
	return 0;
}
