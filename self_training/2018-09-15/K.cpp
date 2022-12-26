#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 65;
int t, n, m, d;
ULL mat[3][maxn];
void mat_mul(int n, ULL lft[], ULL rht[], ULL res[]) {
	memset(res, 0, n * sizeof(ULL));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if((lft[i] >> j) & 1)
				res[i] ^= rht[j];
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &m, &d);
		ULL vec1 = 0, vec2 = 0;
		for(int i = 0, idx = 0; i < n; ++i)
			for(int j = 0; j < n; ++j, ++idx) {
				int x;
				scanf("%d", &x);
				vec1 ^= (ULL)(x & 1) << idx;
			}
		for(int i = 0, idx = 0; i < m; ++i)
			for(int j = 0; j < m; ++j, ++idx) {
				int x;
				scanf("%d", &x);
				vec2 ^= (ULL)(x & 1) << idx;
			}
		memset(mat, 0, sizeof mat);
		int cur = 0, pre = 1, res = 2;
		for(int i = 0; i < n * n; ++i) {
			int x1 = i / n, y1 = i % n;
			for(int j = 0; j < m * m; ++j) {
				int x2 = x1 + j / m - (m >> 1), y2 = y1 + j % m - (m >> 1);
				if(x2 >= 0 && x2 < n && y2 >= 0 && y2 < n && ((vec2 >> j) & 1))
					mat[cur][x2 * n + y2] ^= 1ULL << i;
			}
		}
		for(int i = 0; i < n * n; ++i)
			mat[res][i] ^= 1ULL << i;
		while(d > 0) {
			if(d & 1) {
				mat_mul(n * n, mat[res], mat[cur], mat[pre]);
				swap(res, pre);
			}
			d >>= 1;
			mat_mul(n * n, mat[cur], mat[cur], mat[pre]);
			swap(cur, pre);
		}
		vec2 = 0;
		for(int j = 0; j < n * n; ++j)
			if((vec1 >> j) & 1)
					vec2 ^= mat[res][j];
		int ans = 0;
		for(int j = 0; j < n * n; ++j)
			ans += (vec2 >> j) & 1;
		printf("%d\n", ans);
	}
	return 0;
}
