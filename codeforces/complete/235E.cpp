#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e3 + 1, maxm = (int)9e3 + 1;
int A, B, C, mx, mu[maxn], f[maxn], g[maxn], h[maxn];
int cnt, ord[maxn], rnk[maxn], tot, lnk[maxn], pos[maxn];
struct Edge {
	int nxt, v, idx;
} e[maxm];
int main() {
	scanf("%d%d%d", &A, &B, &C);
	mx = max(A, max(B, C));
	for(int i = 1; i <= mx; ++i) {
		f[i] = A / i;
		g[i] = B / i;
		h[i] = C / i;
	}
	++mu[1];
	for(int i = 1; i <= mx; ++i)
		for(int j = i + i; j <= mx; j += i) {
			mu[j] -= mu[i];
			f[i] += f[j];
			g[i] += g[j];
			h[i] += h[j];
		}
	for(int i = 1; i <= mx; ++i) if(mu[i]) {
		ord[++cnt] = i;
		for(int x = i + i; x <= mx; x += i) if(mu[x])
			for(int y = i, j = x; y < x && j <= mx; y += i, j += x) if(mu[j] && (f[j] || g[j] || h[j])) {
				++rnk[x];
				++rnk[y];
			}
	}
	sort(ord + 1, ord + cnt + 1, [&](int const &u, int const &v) {
		return rnk[u] < rnk[v] || (rnk[u] == rnk[v] && u < v);
	});
	for(int i = 1; i <= cnt; ++i)
		rnk[ord[i]] = i;
	for(int i = 1; i <= mx; ++i) if(mu[i])
		for(int x = i + i; x <= mx; x += i) if(mu[x])
			for(int y = i, j = x; y < x && j <= mx; y += i, j += x) if(mu[j] && (f[j] || g[j] || h[j])) {
				int u = x, v = y;
				if(rnk[u] < rnk[v])
					swap(u, v);
				e[++tot] = (Edge){lnk[u], v, j};
				lnk[u] = tot;
			}
	int ans = 0;
	for(int o = cnt; o >= 1; --o) {
		int i = ord[o];
		for(int it = lnk[i]; it; it = e[it].nxt)
			pos[e[it].v] = e[it].idx;
		ans += f[i] * g[i] * h[i] * mu[i];
		for(int it = lnk[i]; it; it = e[it].nxt) {
			int j = e[it].v, idx1 = e[it].idx;
			ans += f[idx1] * g[idx1] * (h[i] * mu[j] + mu[i] * h[j])
				+ (f[idx1] * (g[i] * mu[j] + mu[i] * g[j])
					+ (f[i] * mu[j] + mu[i] * f[j]) * g[idx1]) * h[idx1];
			for(int jt = lnk[j]; jt; jt = e[jt].nxt) {
				if(!pos[e[jt].v])
					continue;
				int k = e[jt].v, idx2 = e[jt].idx, idx3 = pos[k];
				ans += ((f[idx1] * g[idx2] + f[idx2] * g[idx1]) * h[idx3]
					+ (f[idx1] * g[idx3] + f[idx3] * g[idx1]) * h[idx2]
					+ (f[idx2] * g[idx3] + f[idx3] * g[idx2]) * h[idx1]) * mu[i] * mu[j] * mu[k];
			}
		}
		for(int it = lnk[i]; it; it = e[it].nxt)
			pos[e[it].v] = 0;
	}
	printf("%d\n", ans & ((1 << 30) - 1));
	return 0;
}
