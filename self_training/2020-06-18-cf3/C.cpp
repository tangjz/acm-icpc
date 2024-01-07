#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)5e5 + 1;
const int mod = (int)1e9 + 7;


int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n, k;
		static char buf[maxn];
		scanf("%d%d%s", &n, &k, buf);
		int las = -1, ans = 0;
		auto calc = [&](int len, bool sp = false) {
			if(sp) {
				// x * (k + 1) <= len
				ans += len / (k + 1);
			} else if(len >= k) {
				// x * (k + 1) + k <= len
				ans += (len - k) / (k + 1);
			}
		};
		for(int i = 0; i < n; ++i)
			if(buf[i] == '1') {
				calc(i - las - 1, las == -1);
				las = i;
			}
		if(las == -1) {
			// (x - 1) * (k + 1) + 1 <= n
			ans += (n - 1) / (k + 1) + 1;
		} else {
			calc(n - las - 1, 1);
		}
		printf("%d\n", ans);
		// printf("Case #%d:");
	}

	return 0;
}