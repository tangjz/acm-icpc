/*
 * 超级暴力的最长公共子序列
 * 注意内存限制
 */
#include <cstdio>
#include <cstring>
const int maxl = 501;
int n, m, p, f[2][maxl][maxl];
char S[maxl], T[maxl], Q[maxl];
inline int min(int a, int b) { return a < b ? a : b; }
inline void upd(int &a, int b) { if(a < b) a = b; }
int main()
{
	scanf("%s%s%s", S, T, Q);
	n = strlen(S), m = strlen(T), p = strlen(Q);
	memset(f[0], -1, sizeof f[0]);
	for(int i = 0; i <= m; ++i)
		f[0][i][0] = 0;
	for(int i = 0, now = 0; i <= n; ++i)
	{
		memset(f[now ^ 1], -1, sizeof f[0]);
		f[now][0][0] = 0;
		for(int j = 0; j <= m; ++j)
		{
			int lim = min(min(i, j), p);
			for(int k = 0; k <= lim; ++k)
			{
				if(f[now][j][k] == -1) continue;
				if(i < n) upd(f[now ^ 1][j][k], f[now][j][k]);
				if(j < m) upd(f[now][j + 1][k], f[now][j][k]);
				if(i < n && j < m && S[i] == T[j])
				{
					upd(f[now ^ 1][j + 1][k], f[now][j][k] + 1);
					if(k < p && S[i] == Q[k]) upd(f[now ^ 1][j + 1][k + 1], f[now][j][k] + 1);
				}
			}
		}
		now ^= 1;
	}
	if(f[n & 1][m][p] == -1) puts("NO SOLUTION");
	else printf("%d\n", f[n & 1][m][p]);
	return 0;
}
