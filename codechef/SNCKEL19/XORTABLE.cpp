#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e3 + 1, maxm = (int)1e6 + 1;
int t, n, m, low[maxn], upp[maxn], mat[maxn][maxn], ans[maxn], qtot, que[maxn], dis[maxn], etot, vtot, val[maxm], ctr[maxm];
pair<int, int> eve[maxm];
bool vis[maxn];
void addEvent(int dep, int lft, int low, int upp, int msk) {
	int rht = lft + (1 << dep) - 1;
	if(low <= lft && rht <= upp) {
		int mask = (msk >> dep) << dep;
		eve[etot++] = make_pair(lft ^ mask, rht ^ mask);
		return;
	}
	int mid = lft + (1 << (dep - 1));
	if(low < mid)
		addEvent(dep - 1, lft, low, upp, msk);
	if(upp >= mid)
		addEvent(dep - 1, mid, low, upp, msk);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n + m; ++i) {
			scanf("%d%d", low + i, upp + i);
			vis[i] = 0;
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				scanf("%d", mat[i] + j);
		bool chk = 1;
		for(int u = 0; u < n + m; ++u) {
			if(vis[u])
				continue;
			qtot = 0;
			vis[u] = 1;
			dis[u] = 0;
			que[qtot++] = u;
			for(int i = 0; i < qtot; ++i) {
				int u = que[i];
				if(u < n) {
					for(int j = 0; chk && j < i; ++j)
						chk &= que[j] < n || mat[u][que[j] - n] == -1 || mat[u][que[j] - n] == (dis[u] ^ dis[que[j]]);
					if(!chk)
						break;
					for(int j = 0; j < m; ++j)
						if(mat[u][j] != -1 && !vis[n + j]) {
							vis[n + j] = 1;
							dis[n + j] = dis[u] ^ mat[u][j];
							que[qtot++] = n + j;
						}
				} else {
					for(int j = 0; chk && j < i; ++j)
						chk &= que[j] >= n || mat[que[j]][u - n] == -1 || mat[que[j]][u - n] == (dis[u] ^ dis[que[j]]);
					if(!chk)
						break;
					for(int j = 0; j < n; ++j)
						if(mat[j][u - n] != -1 && !vis[j]) {
							vis[j] = 1;
							dis[j] = dis[u] ^ mat[j][u - n];
							que[qtot++] = j;
						}
				}
			}
			if(!chk)
				break;
			etot = 0;
			for(int i = 0; i < qtot; ++i)
				addEvent(30, 0, low[que[i]], upp[que[i]], dis[que[i]]);
			vtot = 0;
			for(int i = 0; i < etot; ++i) {
				val[vtot++] = eve[i].first;
				val[vtot++] = eve[i].second + 1;
			}
			sort(val, val + vtot);
			vtot = unique(val, val + vtot) - val;
			memset(ctr, 0, vtot * sizeof(int));
			for(int i = 0; i < etot; ++i) {
				int L = lower_bound(val, val + vtot, eve[i].first) - val;
				int R = lower_bound(val, val + vtot, eve[i].second + 1) - val;
				++ctr[L];
				--ctr[R];
			}
			for(int i = 1; i < vtot; ++i)
				ctr[i] += ctr[i - 1];
			chk = 0;
			for(int i = 0; i < vtot; ++i)
				if(ctr[i] == qtot) {
					chk = 1;
					for(int j = 0; j < qtot; ++j)
						ans[que[j]] = val[i] ^ dis[que[j]];
					break;
				}
			if(!chk)
				break;
		}
		if(chk) {
			puts("YES");
			for(int i = 0; i < n + m; ++i)
				printf("%d%c", ans[i], " \n"[i == n - 1 || i == n + m - 1]);
		} else {
			puts("NO");
		}
	}
	return 0;
}