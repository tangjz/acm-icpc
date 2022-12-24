#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)4e3 + 1;
int n, m, q, a[maxn], b[maxn], cur, pre = 1;
short f[maxn][maxn], g[maxn][maxn], h[2][maxn];
void init(int n, int m, int seq[], short nxt[][maxn]) {
	for(int i = 0; i < n; ++i)
		scanf("%d", seq + i);
	for(int i = 0; i < m; ++i)
		nxt[n][i] = n;
	for(int i = n - 1; i >= 0; --i) {
		memcpy(nxt[i], nxt[i + 1], m * sizeof(short));
		nxt[i][--seq[i]] = i;
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	init(n, q, a, f);
	init(m, q, b, g);
	memset(h[cur], -1, (n + 1) * sizeof(short));
	for(int i = 0; i < q; ++i)
		h[cur][f[0][i]] = g[0][i];
	for(int i = 1; ; ++i) {
		if(h[cur][n] == m) {
			printf("%d\n", i);
			break;
		}
		swap(cur, pre);
		memset(h[cur], -1, (n + 1) * sizeof(short));
		for(int j = 0; j <= n; ++j) {
			if(h[pre][j] == -1)
				continue;
			for(int k = 0; k < q; ++k) {
				short u = j < n ? f[j + 1][k] : n;
				short v = h[pre][j] < m ? g[h[pre][j] + 1][k] : m;
				h[cur][u] = max(h[cur][u], v);
			}
		}
	}
	return 0;
}
