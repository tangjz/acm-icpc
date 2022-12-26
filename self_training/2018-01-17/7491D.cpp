#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, int> Node;
const int maxn = (int)3e5 + 1, maxm = 101;
const LL INF = (LL)2e18;
int n, q, tot;
LL a[maxn];
Node b[maxm];
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%lld", a + i);
	while(q--) {
		int L, R;
		scanf("%d%d", &L, &R);
		if(R - L + 1 < 3) {
			puts("-1");
			continue;
		}
		tot = 0;
		for(int i = L; i <= R && tot < maxm; ++i)
			b[tot++] = (Node){a[i], i};
		sort(b, b + tot);
		for( ; tot >= 3; --tot)
			if(b[tot - 1].first < b[tot - 2].first + b[tot - 3].first) {
				printf("%d %d %d\n", b[tot - 1].second, b[tot - 2].second, b[tot - 3].second);
				break;
			}
		if(tot < 3)
			puts("-1");
	}
	return 0;
}
