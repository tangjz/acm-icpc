#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxd = 21;
int n, m, lim, a[maxn], mx, fa[maxd][maxn];
int main() {
	scanf("%d%d%d", &n, &m, &lim);
	for(int i = 1, las = 0, sum = 0; i <= n; ++i) {
		scanf("%d", a + i);
		for(sum += a[i]; sum > lim; sum -= a[++las]);
		fa[0][i] = las;
	}
	for(mx = 0; 1 << mx <= n; ++mx);
	for(int i = 1; i < mx; ++i)
		for(int j = 1; j <= n; ++j)
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
	while(m--) {
		int L, R, ans = 0;
		scanf("%d%d", &L, &R);
		for(int i = mx - 1; i >= 0; --i)
			if(fa[i][R] >= L) {
				R = fa[i][R];
				ans += 1 << i;
			}
		if(L <= R) {
			R = fa[0][R];
			++ans;
		}
		if(L <= R) {
			puts("Chtholly");
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
}
