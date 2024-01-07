#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, INF = 0x3f3f3f3f;
int t, n, pL[maxn], pR[maxn], sz[maxn], seq[maxn][4], f[maxn][4];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", pL + i, pR + i);
		for(int i = 1, qL = -INF, qR = INF; i <= n; ++i) {
			qL = max(qL, pL[i]);
			qR = min(qR, pR[i]);
			sz[i] = 0;
			for(int j = 0; j < 2 && pL[i] + j <= pR[i]; ++j) {
				seq[i][sz[i]++] = pL[i] + j;
				seq[i][sz[i]++] = pR[i] - j;
			}
			sort(seq[i], seq[i] + sz[i]);
			sz[i] = unique(seq[i], seq[i] + sz[i]) - seq[i];
			for(int j = 0; j < sz[i]; ++j)
				f[i][j] = qL <= seq[i][j] && seq[i][j] <= qR ? 0 : INF;
			for(int j = i - 1, rL = -INF, rR = INF; j >= 1; --j) {
				rL = max(rL, pL[j]);
				rR = min(rR, pR[j]);
				if(rL > rR)
					break;
				for(int k = 0; k < sz[j]; ++k)
					if(rL <= seq[j][k] && seq[j][k] <= rR)
						for(int o = 0; o < sz[i]; ++o) {
							int dis = abs(seq[i][o] - seq[j][k]);
							dis = (dis + 1) >> 1;
							f[i][o] = min(f[i][o], f[j][k] + dis);
						}
			}
		}
		int ans = INF;
		for(int i = n, qL = -INF, qR = INF; i >= 1; --i) {
			qL = max(qL, pL[i]);
			qR = min(qR, pR[i]);
			for(int j = 0; j < sz[i]; ++j)
				if(qL <= seq[i][j] && seq[i][j] <= qR)
					ans = min(ans, f[i][j]);
		}
		printf("%d\n", ans);
	}
	return 0;
}