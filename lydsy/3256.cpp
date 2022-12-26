/*
 * 先做一次kmp加速dp，用f[i,j,k]表示S串前i位，T串前j位的某个子序列匹配Q串到第k位的最大长度
 * 剩下一切都和最长公共子序列dp一样
 */
#include <cstdio>
const int maxl = 202;
int n, m, p, F[maxl], f[maxl][maxl][maxl], ans;
char S[maxl], T[maxl], Q[maxl];
inline void upd(int &a, int b) { if(a < b) a = b; }
int main()
{
	scanf("%d%d%d%s%s%s", &n, &m, &p, S, T, Q);
	for(int i = 1, j; i < p; ++i)
	{
		j = F[i];
		while(j && Q[i] != Q[j]) j = F[j];
		if(Q[i] == Q[j]) F[i + 1] = j + 1;
	}
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= m; ++j)
			for(int k = 0; k < p; ++k)
			{
				if(!f[i][j][k] && k) continue;
				if(i < n) upd(f[i + 1][j][k], f[i][j][k]);
				if(j < m) upd(f[i][j + 1][k], f[i][j][k]);
				if(i < n && j < m && S[i] == T[j])
				{
					int kk = k;
					while(kk && S[i] != Q[kk]) kk = F[kk];
					if(S[i] == Q[kk]) ++kk;
					upd(f[i + 1][j + 1][kk], f[i][j][k] + 1);
				}
				if(i == n && j == m) upd(ans, f[i][j][k]);
			}
	printf("%d\n", ans);
	return 0;
}
