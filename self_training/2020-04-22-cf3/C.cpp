#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;
int t, n, m, c[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		m = 0;
		memset(c + 1, 0, n * sizeof(int));
		for(int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			m += !c[x];
			++c[x];
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i) {
			if(!c[i])
				continue;
			ans = max(ans, min(c[i], m - 1));
			ans = max(ans, min(c[i] - 1, m));
		}
		printf("%d\n", ans);
	}
	return 0;
}