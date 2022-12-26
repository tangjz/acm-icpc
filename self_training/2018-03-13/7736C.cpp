#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int n, m, ds, cs, da, ca, h[maxn];
int main() {
	scanf("%d%d%d%d%d%d", &n, &m, &ds, &cs, &da, &ca);
	for(int i = 0; i < n; ++i)
		scanf("%d", h + i);
	sort(h, h + n);
	int ans = 0;
	for(int i = 0; i * ca <= m; ++i) {
		int dmg = i * da, rem = m - i * ca, ctr = 0;
		for(int j = 0; j < n; ++j) {
			int tmp = (dmg < h[j] ? ((h[j] - dmg - 1) / ds + 1) * cs : 0);
			if(tmp <= rem) {
				++ctr;
				rem -= tmp;
			}
		}
		ans = max(ans, ctr);
	}
	printf("%d\n", ans);
	return 0;
}
