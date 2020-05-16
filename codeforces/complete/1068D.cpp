#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxm = 201, mod = 998244353;
int n, a[maxn], f[2][2][maxm], cur, pre = 1;
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	if(a[0] == -1) {
		for(int i = 1; i < maxm; ++i)
			f[cur][0][i] = 1;
	} else {
		f[cur][0][a[0]] = 1;
	}
	for(int i = 1; i < n; ++i) {
		swap(cur, pre);
		memset(f[cur], 0, sizeof f[0]);
		int lft[2] = {}, rht[2] = {};
		for(int j = 1; j < maxm; ++j) {
			mod_inc(rht[0], f[pre][0][j]);
			mod_inc(rht[1], f[pre][1][j]);
		}
		for(int j = 1; j < maxm; ++j) {
			if(a[i] == -1 || a[i] == j) {
				mod_inc(f[cur][0][j], lft[0]);
				mod_inc(f[cur][0][j], lft[1]);
				mod_inc(f[cur][1][j], rht[1]);
				mod_inc(f[cur][1][j], f[pre][0][j]);
			}
			mod_inc(lft[0], f[pre][0][j]);
			mod_inc(lft[1], f[pre][1][j]);
			mod_inc(rht[0], mod - f[pre][0][j]);
			mod_inc(rht[1], mod - f[pre][1][j]);
		}
	}
	int ans = 0;
	for(int i = 1; i < maxm; ++i)
		mod_inc(ans, f[cur][1][i]);
	printf("%d\n", ans);
	return 0;
}