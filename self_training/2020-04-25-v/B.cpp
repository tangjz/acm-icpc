#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;
int n, a[maxn], pre[maxn];
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		int k, x;
		LL mul = 1;
		scanf("%d%d%d", &n, &k, &x);
		for(int i = 0; i < k; ++i)
			mul *= x;
		pre[0] = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%d", a + i);
			pre[i + 1] = pre[i] | a[i];
		}
		int suf = 0;
		LL ans = 0;
		for(int i = n - 1; i >= 0; --i) {
			LL tmp = pre[i] | (a[i] * mul) | suf;
			ans = max(ans, tmp);
			suf |= a[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}