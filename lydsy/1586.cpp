#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 53, mod = (int)1e6 + 7;
int n, row, col, seq[maxn << 1 | 1], ord[maxn];
int c[maxn << 1 | 1][maxn], f[maxn][maxn], g[maxn][maxn];
bool cmp(int const &u, int const &v) {
	return seq[u] < seq[v] || (seq[u] == seq[v] && seq[n + u] < seq[n + v]);
}
int main() {
	scanf("%d%d", &row, &col);
	for( ; scanf("%d", seq + n) == 1; ++n);
	n >>= 1;
	seq[n + n + 3] = col;
	for(int i = n; i > 0; --i)
		seq[n + i + 2] = seq[n + i - 1];
	seq[n + 2] = 1;
	seq[n + 1] = row;
	for(int i = n; i > 0; --i)
		seq[i] = seq[i - 1];
	seq[0] = 1;
	n += 2;
	for(int i = 0; i < n; ++i)
		ord[i] = i;
	sort(ord + 1, ord + n - 1, cmp);
	for(int i = 0; i <= row + col - 2; ++i) {
		c[i][0] = 1;
		for(int j = 1; j <= i && j < row; ++j)
			(c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod && (c[i][j] -= mod);
	}
	for(int i = 0; i < n; ++i) {
		int u = ord[i];
		for(int j = i + 1; j < n; ++j) {
			int v = ord[j], dx = seq[v] - seq[u], dy = seq[n + v] - seq[n + u];
			if(dy < 0)
				continue;
			f[u][v] = c[dx + dy][dx];
			for(int k = i + 1; k < j; ++k) {
				int w = ord[k], dx = seq[v] - seq[w], dy = seq[n + v] - seq[n + w];
				if(dy < 0)
					continue;
				f[u][v] = (f[u][v] - (LL)f[u][w] * c[dx + dy][dx]) % mod;
			}
			f[u][v] < 0 && (f[u][v] += mod);
		}
	}
	if(n > 1 && seq[0] == seq[ord[1]] && seq[n] == seq[n + ord[1]]) {
		g[ord[1]][1] = 1;
	} else {
		g[0][0] = 1;
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j <= i; ++j) {
			if(!g[i][j])
				continue;
			for(int k = i + 1; k < n; ++k)
				if(f[i][k])
					g[k][j + 1] = (g[k][j + 1] + (LL)g[i][j] * f[i][k]) % mod;
		}
	int *G = n > 1 && seq[ord[n - 2]] == seq[n - 1] && seq[n + ord[n - 2]] == seq[n + n - 1] ? g[ord[n - 2]] : g[n - 1] + 1;
	n -= 2;
	for(int i = 0; i <= n; ++i)
		printf("%d%c", G[i], " \n"[i == n]);
	return 0;
}
