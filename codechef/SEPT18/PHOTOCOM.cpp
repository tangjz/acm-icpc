#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1;
int t, row[2], col[2];
char buf[2][maxn];
LL cnt[4][maxn], ans;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%s", row + 0, col + 0, buf[0]);
		scanf("%d%d%s", row + 1, col + 1, buf[1]);
		int rcom = __gcd(row[0], row[1]), rmul[2] = {row[1] / rcom, row[0] / rcom};
		int ccom = __gcd(col[0], col[1]), cmul[2] = {col[1] / ccom, col[0] / ccom};
		ans = 0;
		for(LL j1 = 0; j1 < col[1]; ++j1)
			cnt[0][j1] = cnt[1][j1] = cnt[2][j1] = cnt[3][j1] = 0;
		for(LL i0 = 0, i1 = 0, x0 = 0, x1 = rmul[1] - 1; i1 < row[1]; ++i1, x1 += rmul[1]) {
			for( ; i0 < row[0] && x0 <= x1; ++i0, x0 += rmul[0])
				for(LL j0 = 0, j1 = 0, y0 = 0, y1 = cmul[1] - 1, idx0 = i0 * col[0]; j0 < col[0]; ++j0, y0 += cmul[0], ++idx0) {
					for( ; y0 > y1; ++j1, y1 += cmul[1]);
					int v = (buf[0][idx0] == '0') + (i0 && j0 && buf[0][idx0 - col[0] - 1] == '0') - (i0 && buf[0][idx0 - col[0]] == '0') - (j0 && buf[0][idx0 - 1] == '0');
					if(v) {
						cnt[0][j1] += v;
						cnt[1][j1] += v * x0;
						cnt[2][j1] += v * y0;
						cnt[3][j1] += v * x0 * y0;
					}
				}
			for(LL j1 = 0, y1 = cmul[1] - 1, idx1 = i1 * col[1], ctr[4] = {}; j1 < col[1]; ++j1, y1 += cmul[1], ++idx1) {
				ctr[0] += cnt[0][j1];
				ctr[1] += cnt[1][j1];
				ctr[2] += cnt[2][j1];
				ctr[3] += cnt[3][j1];
				int v = (buf[1][idx1] == '0') + (i1 + 1 < row[1] && j1 + 1 < col[1] && buf[1][idx1 + col[1] + 1] == '0') - (i1 + 1 < row[1] && buf[1][idx1 + col[1]] == '0') - (j1 + 1 < col[1] && buf[1][idx1 + 1] == '0');
				if(v)
					ans += v * (ctr[0] * (x1 + 1) * (y1 + 1) - ctr[1] * (y1 + 1) - ctr[2] * (x1 + 1) + ctr[3]);
			}
		}
		for(LL j1 = 0; j1 < col[1]; ++j1)
			cnt[0][j1] = cnt[1][j1] = cnt[2][j1] = cnt[3][j1] = 0;
		for(LL i0 = 0, i1 = 0, x0 = 0, x1 = rmul[1] - 1; i1 < row[1]; ++i1, x1 += rmul[1]) {
			for( ; i0 < row[0] && x0 <= x1; ++i0, x0 += rmul[0])
				for(LL j0 = 0, j1 = 0, y0 = 0, y1 = cmul[1] - 1, idx0 = i0 * col[0]; j0 < col[0]; ++j0, y0 += cmul[0], ++idx0) {
					for( ; y0 > y1; ++j1, y1 += cmul[1]);
					int v = (buf[0][idx0] == '1') + (i0 && j0 && buf[0][idx0 - col[0] - 1] == '1') - (i0 && buf[0][idx0 - col[0]] == '1') - (j0 && buf[0][idx0 - 1] == '1');
					if(v) {
						cnt[0][j1] += v;
						cnt[1][j1] += v * x0;
						cnt[2][j1] += v * y0;
						cnt[3][j1] += v * x0 * y0;
					}
				}
			for(LL j1 = 0, y1 = cmul[1] - 1, idx1 = i1 * col[1], ctr[4] = {}; j1 < col[1]; ++j1, y1 += cmul[1], ++idx1) {
				ctr[0] += cnt[0][j1];
				ctr[1] += cnt[1][j1];
				ctr[2] += cnt[2][j1];
				ctr[3] += cnt[3][j1];
				int v = (buf[1][idx1] == '1') + (i1 + 1 < row[1] && j1 + 1 < col[1] && buf[1][idx1 + col[1] + 1] == '1') - (i1 + 1 < row[1] && buf[1][idx1 + col[1]] == '1') - (j1 + 1 < col[1] && buf[1][idx1 + 1] == '1');
				if(v)
					ans += v * (ctr[0] * (x1 + 1) * (y1 + 1) - ctr[1] * (y1 + 1) - ctr[2] * (x1 + 1) + ctr[3]);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
