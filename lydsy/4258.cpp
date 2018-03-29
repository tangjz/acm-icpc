#include <bits/stdc++.h>
const int maxn = 1001, maxm = 11, maxd = 1 << 10 | 1, mod = (int)1e9 + 7;
const char *pat = "AGCT";
int n, m, bits[maxd], msk[4], tr[4][maxd], f[2][maxd], cur, pre = 1, ans[maxm];
char buf[maxm];
int main() {
	scanf("%s%d", buf, &n);
	m = strlen(buf);
	for(int i = 1; i < 1 << m; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < 4; ++j)
			if(buf[i] == pat[j])
				msk[j] |= 1 << i;
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 1 << m; ++j) {
			int tmp = j | msk[i];
			tr[i][j] = tmp & (tmp ^ (tmp - (j << 1 | 1)));
		}
	f[cur][0] = 1;
	for(int i = 0; i < n; ++i) {
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], 0, (1 << m) * sizeof(int));
		for(int j = 0; j < 4; ++j)
			for(int k = 0; k < 1 << m; ++k)
				(f[cur][tr[j][k]] += f[pre][k]) >= mod && (f[cur][tr[j][k]] -= mod);
	}
	for(int i = 0; i < 1 << m; ++i)
		(ans[bits[i]] += f[cur][i]) >= mod && (ans[bits[i]] -= mod);
	for(int i = 0; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
