#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 501;
int n, m, xx, yy, zz, mat[maxn][maxn], c[maxn], cc[maxn];
LL s[maxn], ss[maxn], ans;
int main() {
	scanf("%d%d%d%d%d", &n, &m, &xx, &yy, &zz);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d", mat[i] + j);
	for(int xL = 1; xL <= n; ++xL) {
		memset(c + 1, 0, m * sizeof(int));
		memset(s + 1, 0, m * sizeof(LL));
		for(int xR = xL; xR <= n && xR - xL + 1 <= xx; ++xR) {
			int L = 0, R = 0;
			static int que[maxn];
			que[R++] = 0;
			for(int y = 1; y <= m; ++y) {
				c[y] += !mat[xR][y];
				cc[y] = cc[y - 1] + c[y];
				s[y] += mat[xR][y];
				ss[y] = ss[y - 1] + s[y];
				for( ; L < R && !(y - que[L] <= yy && cc[y] - cc[que[L]] <= zz); ++L);
				if(L < R)
					ans = max(ans, ss[y] - ss[que[L]]);
				for( ; L < R && ss[y] <= ss[que[R - 1]]; --R);
				que[R++] = y;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}

