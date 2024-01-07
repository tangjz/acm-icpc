#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)3e5 + 1, mod = (int)1e9 + 7;
int n, a[maxn];
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, a + 0);
		int ans = 0, cur = 0;
		for(int i = 1; i < n; ++i) {
			scanf("%d", a + i);
			if(abs(a[i] - a[i - 1]) <= 2) {
				++cur;
			} else {
				cur = 0;
			}
			ans = max(ans, cur);
		}
		printf("%d\n", ans + 1);
	}
	return 0;
}