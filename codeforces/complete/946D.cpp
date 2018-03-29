#include <bits/stdc++.h>
using namespace std;
const int maxn = 501, INF = 0x3f3f3f3f;
int n, m, q, f[maxn], g[maxn], tot, seq[maxn];
char buf[maxn];
int main() {
	scanf("%d%d%d", &n, &m, &q);
	while(n--) {
		scanf("%s", buf);
		tot = 0;
		for(int i = 0; i < m; ++i)
			if(buf[i] == '1')
				seq[tot++] = i;
		for(int i = 0; i < tot; ++i) {
			g[i] = INF;
			for(int j = 0, k = tot - 1 - i; k < tot; ++j, ++k)
				g[i] = min(g[i], seq[k] - seq[j] + 1);
		}
		g[tot] = 0;
		for(int i = q; i >= 0; --i) {
			f[i] += g[0];
			for(int j = 1; j <= tot && j <= i; ++j)
				f[i] = min(f[i], f[i - j] + g[j]);
		}
	}
	printf("%d\n", f[q]);
	return 0;
}
