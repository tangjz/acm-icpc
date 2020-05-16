#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 3, INF = 0x3f3f3f3f;
int n, pre[maxn][2], suf[maxn][2];
pair<int, int> a[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[i] = make_pair(x + y, x - y);
	}
	sort(a + 1, a + n + 1);
	pre[0][0] = suf[n + 1][0] = INF;
	pre[0][1] = suf[n + 1][1] = -INF;
	for(int i = 1; i <= n; ++i) {
		pre[i][0] = min(pre[i - 1][0], a[i].second);
		pre[i][1] = max(pre[i - 1][1], a[i].second);
	}
	for(int i = n; i >= 1; --i) {
		suf[i][0] = min(suf[i + 1][0], a[i].second);
		suf[i][1] = max(suf[i + 1][1], a[i].second);
	}
	int L = 0, R = max(a[n].first - a[1].first, pre[n][1] - pre[n][0]);
	while(L < R) {
		int M = L + (R - L) / 2;
		bool chk = 0;
		for(int i = 1, j = 1; !chk && i <= n; ++i) {
			for( ; j <= n && a[j].first - a[i].first <= M; ++j);
			chk |= max(pre[i - 1][1], suf[j][1]) - min(pre[i - 1][0], suf[j][0]) <= M;
		}
		if(!chk) {
			L = M + 1;
		} else {
			R = M;
		}
	}
	printf("%d.%c\n", L >> 1, "05"[L & 1]);
	return 0;
}