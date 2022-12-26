#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1, maxd = 61;
int n, pos[maxd], ans;
pair<int, LL> a[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%lld%d", &a[i].second, &a[i].first);
	sort(a, a + n);
	memset(pos, -1, sizeof pos);
	for(int i = n - 1; i >= 0; --i)
		for(int j = maxd - 1; j >= 0; --j) {
			if(!((a[i].second >> j) & 1))
				continue;
			if(pos[j] == -1) {
				pos[j] = i;
				ans += a[i].first;
				break;
			} else {
				a[i].second ^= a[pos[j]].second;
			}
		}
	printf("%d\n", ans);
	return 0;
}
