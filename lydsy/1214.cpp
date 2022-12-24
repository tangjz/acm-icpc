#include <bits/stdc++.h>
const int maxn = 751;
int n, m, h[maxn], tot, stk[maxn];
long long c[maxn][maxn], ans, mx;
char buf[maxn][maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", buf[i]);
	for(int i = n - 1; i >= 0; --i)
		for(int j = tot = 0; j <= m; ++j) {
			h[j] = buf[i][j] == '1' ? h[j] + 1 : 0;
			for( ; tot && h[stk[tot - 1]] >= h[j]; --tot) {
				int k = 0, low = h[j], upp = h[stk[tot - 1]];
				if(tot > 1) {
					k = stk[tot - 2] + 1;
					low < h[stk[tot - 2]] && (low = h[stk[tot - 2]]);
				}
				int dx = upp - low, dy = j - k;
				if(!dx)
					continue;
				ans += dx * dy * (dy + 1) / 2;
				int px[4][2] = {{i, dx}, {i + 1, -dx}, {i + low + 1, -1}, {i + upp + 1, 1}};
				int py[4][2] = {{k, dy}, {k + 1, -dy - 2}, {j + 1, dy + 2}, {j + 2, -dy}};
				for(int u = 0; u < 4; ++u)
					if(px[u][0] < n)
						for(int v = 0; v < 4; ++v)
							if(py[v][0] < m)
								c[px[u][0]][py[v][0]] += px[u][1] * py[v][1];
			}
			stk[tot++] = j;
		}
	for(int i = 0; i < n; ++i) {
		for(int j = 1; j < m; ++j)
			c[i][j] += c[i][j - 1];
		for(int j = 1; j < m; ++j)
			c[i][j] += c[i][j - 1];
		for(int j = 1; j < m; ++j)
			c[i][j] += c[i][j - 1];
	}
	for(int i = 1; i < n; ++i)
		for(int j = 0; j < m; ++j)
			c[i][j] += c[i - 1][j];
	for(int i = 1; i < n; ++i)
		for(int j = 0; j < m; ++j)
			c[i][j] += c[i - 1][j];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			mx < c[i][j] && (mx = c[i][j]);
	printf("%lld\n", ans - mx);
	return 0;
}
