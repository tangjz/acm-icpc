#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxd = 8, maxs = 1 << (maxd + 3) | 1, INF = 0x3f3f3f3f;
int n, m, que[maxn], f[maxn], low[maxd | 1][maxd | 1], msk[maxn], cnt[maxs], g[maxs][maxs];
LL ans[maxd << 1 | 1];
char buf[maxn];
vector<int> e[maxd];
int main() {
	scanf("%d%s", &n, buf);
	for(int i = 0; i < n; ++i)
		e[buf[i] -= 'a'].push_back(i);
	memset(low, 0x3f, sizeof low);
	for(int i = maxd - 1; i >= 0; --i) {
		int *D = low[i];
		memset(f, 0x3f, n * sizeof(int));
		m = 0;
		for(auto &u : e[i]) {
			f[u] = 0;
			que[m++] = u;
		}
		if(m)
			D[i] = 0;
		for(int j = 0; j < m; ++j) {
			int u = que[j];
			if(D[buf[u]] == INF) {
				D[buf[u]] = f[u];
				for(auto &v : e[buf[u]])
					if(f[v] == INF) {
						f[v] = f[u] + 1;
						que[m++] = v;
					}
			}
			if(u && f[u - 1] == INF) {
				f[u - 1] = f[u] + 1;
				que[m++] = u - 1;
			}
			if(u + 1 < n && f[u + 1] == INF) {
				f[u + 1] = f[u] + 1;
				que[m++] = u + 1;
			}
		}
		for(int j = 0; j < n; ++j)
			msk[j] = msk[j] << 1 | (f[j] > D[buf[j]]);
	}
	for(int i = 0; i < n; ++i) {
		msk[i] = msk[i] << 3 | buf[i];
		++cnt[msk[i]];
	}
	for(int i = 0; i < 1 << (maxd + 3); ++i) {
		if(!cnt[i])
			continue;
		auto getDist = [](int u, int v, int *uD, int *vD) {
			int dis = INF;
			for(int k = 0; k < maxd; ++k, u >>= 1, v >>= 1)
				dis = min(dis, uD[k] + (u & 1) + vD[k] + (v & 1) + 1);
			return dis;
		};
		g[i][i] = getDist(i >> 3, i >> 3, low[i & 7], low[i & 7]);
		ans[g[i][i]] += cnt[i] * (cnt[i] - 1LL) / 2;
		for(int j = i + 1; j < 1 << (maxd + 3); ++j) {
			if(!cnt[j])
				continue;
			g[i][j] = g[j][i] = getDist(i >> 3, j >> 3, low[i & 7], low[j & 7]);
			ans[g[i][j]] += (LL)cnt[i] * cnt[j];
		}
	}
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < i + maxd + maxd && j < n; ++j) {
			int pre = g[msk[i]][msk[j]];
			if(j - i < pre) {
				--ans[pre];
				++ans[j - i];
			}
		}
	for(int i = maxd + maxd - 1; i >= 0; --i)
		if(ans[i]) {
			printf("%d %lld\n", i, ans[i]);
			break;
		}
	return 0;
}
