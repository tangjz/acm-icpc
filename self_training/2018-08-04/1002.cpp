#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 26;
int t, n, q, cnt[maxn][maxd + 1];
char buf[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%s", &n, &q, buf);
		for(int i = 1; i <= n; ++i) {
			memcpy(cnt[i], cnt[i - 1], sizeof(cnt[0]));
			++cnt[i][buf[i - 1] - 'A'];
		}
		printf("Case #%d:\n", Case);
		while(q--) {
			int L, R;
			scanf("%d%d", &L, &R);
			for(int i = 0; i < maxd; ++i)
				if(cnt[L - 1][i] != cnt[R][i]) {
					printf("%d\n", cnt[R][i] - cnt[L - 1][i]);
					break;
				}
		}
	}
	return 0;
}
