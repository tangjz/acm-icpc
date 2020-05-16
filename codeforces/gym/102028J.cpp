#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1, maxm = 1501, maxs = maxm * maxm;
int t, n, m, tot, c[maxs], f[maxs], h[maxn], ord[maxs], ord2[maxs];
LL g[maxs];
void addIdx(int x, int y, int id, int typ) {
	if(x < 0 || x >= m || y < 0 || y >= m)
		return;
	int pos = x * m + y;
	LL id2 = (LL)id * id;
	if(typ > 0) {
		++c[pos];
		f[pos] += id;
		g[pos] += id2;
	} else {
		--c[pos];
		f[pos] -= id;
		g[pos] -= id2;
	}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		int all = m * m;
		memset(c, 0, all * sizeof(int));
		memset(f, 0, all * sizeof(int));
		memset(g, 0, all * sizeof(LL));
		for(int i = 0; i < n; ++i) {
			int xL, xR, yL, yR;
			scanf("%d%d%d%d", &xL, &xR, &yL, &yR);
			--xL;
			--yL;
			addIdx(xL, yL, i, 1);
			addIdx(xL, yR, i, -1);
			addIdx(xR, yL, i, -1);
			addIdx(xR, yR, i, 1);
		}
		for(int i = 0, j = 0; i < all; ++i, (++j) == m && (j = 0))
			if(j > 0) {
				c[i] += c[i - 1];
				f[i] += f[i - 1];
				g[i] += g[i - 1];
			}
		for(int i = m, j = 0; i < all; ++i, ++j) {
			c[i] += c[j];
			f[i] += f[j];
			g[i] += g[j];
		}
		int sum = tot = 0;
		memset(h, 0, n * sizeof(int));
		for(int i = 0; i < all; ++i) {
			if(!c[i])
				continue;
			++sum;
			if(c[i] == 1) {
				++h[f[i]];
			} else if(c[i] == 2) {
				int u = f[i], v = (int)sqrt(g[i] + g[i] - (LL)f[i] * f[i]);
				f[i] = (u - v) >> 1;
				g[i] = (u + v) >> 1;
				ord[tot++] = i;
			}
		}
		int mx0 = 0, mx1 = 0;
		for(int i = 0; i < n; ++i)
			if(mx0 < h[i]) {
				mx1 = mx0;
				mx0 = h[i];
			} else if(mx1 < h[i]) {
				mx1 = h[i];
			}
		int ans = mx0 + mx1;
		memset(c, 0, n * sizeof(int));
		for(int i = 0; i < tot; ++i)
			++c[f[ord[i]]];
		for(int i = 1; i < n; ++i)
			c[i] += c[i - 1];
		for(int i = 0; i < tot; ++i)
			ord2[--c[f[ord[i]]]] = ord[i];
		memset(c, 0, n * sizeof(int));
		memset(ord, -1, n * sizeof(int));
		for(int i = 0; i < tot; ++i) {
			int o = ord2[i], u = g[o], v = f[o];
			if(ord[u] != v) {
				if(ord[u] != -1) {
					int tmp = c[u] + h[u] + h[ord[u]];
					if(ans < tmp)
						ans = tmp;
				}
				ord[u] = v;
				c[u] = 1;
			} else {
				++c[u];
			}
		}
		for(int u = 0; u < n; ++u)
			if(ord[u] != -1) {
				int tmp = c[u] + h[u] + h[ord[u]];
				if(ans < tmp)
					ans = tmp;
			}
		printf("%d\n", sum - ans);
	}
	return 0;
}
