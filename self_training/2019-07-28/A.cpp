#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 1 << 10 | 1;
int t, n, m, a[maxn];
bool odd[maxd];
int main() {
	for(int i = 1; i < maxd; ++i)
		odd[i] = odd[i >> 1] ^ (i & 1);
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		set<int> pos;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if(odd[a[i]])
				pos.insert(i);
		}
		printf("Case #%d:", Case);
		for(int i = 1; i <= m; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[++x] = y;
			if(odd[y]) {
				pos.insert(x);
			} else {
				pos.erase(x);
			}
			printf(" %d", n - (pos.size() & 1 ? min(*pos.begin(), n - *pos.rbegin() + 1) : 0));
		}
		printf("\n");
	}
	return 0;
}
