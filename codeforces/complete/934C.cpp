#include <bits/stdc++.h>
using namespace std;
const int maxn = 2003, maxv = 2, INF = 0x3f3f3f3f;
int n, a[maxn], pre[maxn][maxv], suf[maxn][maxv], f[maxv][maxv];
void upd(int &x, int y) {
	x < y && (x = y);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		--a[i];
		for(int j = 0, k = 0; j < maxv; ++j) {
			upd(k, pre[i - 1][j] + (j == a[i]));
			pre[i][j] = k;
		}
	}
	for(int i = n; i >= 1; --i)
		for(int j = maxv - 1, k = 0; j >= 0; --j) {
			upd(k, suf[i + 1][j] + (j == a[i]));
			suf[i][j] = k;
		}
	int ans = pre[n][maxv - 1];
	for(int L = 1; L <= n; ++L) {
		for(int j = 0; j < maxv; ++j)
			for(int k = 0; k <= j; ++k)
				f[j][k] = 0;
		for(int R = L; R <= n; ++R) {
			for(int j = 0; j < maxv; ++j)
				for(int k = j, v = 0; k >= 0; --k) {
					upd(v, f[j][k] + (k == a[R]));
					f[j][k] = v;
					upd(ans, pre[L - 1][k] + v + suf[R + 1][j]);
				}
		}
	}
	printf("%d\n", ans);
	return 0;
}
