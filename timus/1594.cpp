#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 101, p = (int)1e9 + 7;
int n, m, mat[2][maxn][maxn], ans;
int main() {
	scanf("%d%d", &n, &m);
	if((n & 1) && (m & 1)) {
		puts("0");
		return 0;
	}
	if(n > m)
		std::swap(n, m);
	int cur = 0, pre = 1;
	for(int i = 0; i < n; ++i)
		mat[cur][i][i] = 1;
	std::swap(pre, cur);
	for(int i = 0; i < n; ++i) {
		i && (mat[cur][i][i - 1] = 1);
		i + 1 < n && (mat[cur][i][i + 1] = 1);
	}
	for(int i = 2; i <= m; ++i) {
		std::swap(pre, cur);
		for(int j = 0; j < n; ++j)
			for(int k = 0; k < n; ++k) {
				k && (mat[cur][j][k] += mat[pre][j][k - 1]) >= p && (mat[cur][j][k] -= p);
				k + 1 < n && (mat[cur][j][k] += mat[pre][j][k + 1]) >= p && (mat[cur][j][k] -= p);
			}
	}
	ans = 1;
	for(int i = 0; i < n; ++i) {
		int sgn = 1;
		for(int j = i + 1; j < n; ++j)
			while(mat[cur][j][i]) {
				int d = mat[cur][i][i] / mat[cur][j][i];
				for(int k = i; k < n; ++k) {
					(mat[cur][i][k] = (mat[cur][i][k] - (LL)d * mat[cur][j][k]) % p) < 0 && (mat[cur][i][k] += p);
					std::swap(mat[cur][i][k], mat[cur][j][k]);
				}
				sgn = -sgn;
			}
		if(!(i & 1))
			ans = (LL)ans * sgn * mat[cur][i][i] % p;
	}
	ans < 0 && (ans += p);
	if((n & 3) == 2 && (m & 1) && ans)
		ans = p - ans;
	printf("%d\n", ans);
	return 0;
}
