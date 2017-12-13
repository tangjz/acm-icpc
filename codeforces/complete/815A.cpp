#include <cstdio>
const int maxn = 101;
int n, m, a[maxn][maxn], dr[maxn], dc[maxn], rr, cc, cnt;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d", a[i] + j);
	for(int i = 2; i <= n; ++i) {
		dr[i] = a[i][1] - a[i - 1][1];
		for(int j = 2; j <= m; ++j)
			if(dr[i] != a[i][j] - a[i - 1][j]) {
				puts("-1");
				return 0;
			}
		dr[i] += dr[i - 1];
	}
	for(int i = 2; i <= m; ++i) {
		dc[i] = a[1][i] - a[1][i - 1];
		for(int j = 2; j <= n; ++j)
			if(dc[i] != a[j][i] - a[j][i - 1]) {
				puts("-1");
				return 0;
			}
		dc[i] += dc[i - 1];
	}
	cnt = ~0u >> 1;
	for(int r1 = 0, c1 = a[1][1]; r1 <= a[1][1]; ++r1, --c1) {
		bool chk = 1;
		int ctr = 0;
		for(int i = 1; i <= n && chk; ++i) {
			int ri = r1 + dr[i];
			chk &= ri >= 0;
			ctr += ri;
		}
		for(int i = 1; i <= m && chk; ++i) {
			int ci = c1 + dc[i];
			chk &= ci >= 0;
			ctr += ci;
		}
		if(chk && ctr < cnt) {
			cnt = ctr;
			rr = r1;
			cc = c1;
		}
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= n; ++i) {
		int ri = rr + dr[i];
		while(ri--)
			printf("row %d\n", i);
	}
	for(int i = 1; i <= m; ++i) {
		int ci = cc + dc[i];
		while(ci--)
			printf("col %d\n", i);
	}
	return 0;
}
