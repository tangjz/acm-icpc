/*
 * f[i][j][k] 表示 前i行 放j个国王 棋面为k 的 方案数
 * f[i + 1][cnt[j] + cnt[k] -> K][k] = sigma(f[i][K - cnt[k]][j]);
 * j, k为不互斥棋面 cnt为该棋面国王数
 */
#include <cstdio>
int n, K, m;
long long f[10][82][512] = {}, cnt[512] = {}, ans = 0;
bool check1[512] = {}, check2[512][512] = {};
int main()
{
 	int i, j, k, l;
	scanf("%d%d", &n, &K);
	m = (1 << n) - 1;
	for(i = 0; i <= m; ++i)
		if(!(i & (i >> 1)))
		{
			for(k = i; k; k >>= 1) cnt[i] += (k & 1);
			check1[i] = true;
		}
	for(i = 0; i <= m; ++i) if(check1[i])
		for(j = 0; j <= m; ++j) if(check2[j])
			if((i & j) == 0 && (i & (j >> 1)) == 0 && (j & (i >> 1)) == 0)
				check2[i][j] = true;
	for(i = 0; i <= m; ++i) if(check1[i]) f[1][cnt[i]][i] = 1;
	for(i = 1; i < n; ++i)
		for(j = 0; j <= m; ++j) if(check1[j])
			for(k = 0; k <= m; ++k) if(check1[k])
				if(check2[j][k])
					for(l = cnt[j]; l + cnt[k] <= K; ++l)
						f[i + 1][l + cnt[k]][k] += f[i][l][j];
	for(i = 0; i <= m; ++i) ans += f[n][K][i];
	printf("%lld\n", ans);
	return 0;
}
