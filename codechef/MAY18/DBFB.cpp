#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9 + 7;
int t, n, m, cur, pre, x, sum, ans;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &m, &n);
		pre = 1;
		cur = 0;
		for(int i = 1; i < n; ++i) {
			swap(cur, pre);
			(cur += pre) >= mod && (cur -= mod);
		}
		sum = 0;
		for(int i = 0; i < m; ++i) {
			scanf("%d", &x);
			(sum += x) >= mod && (sum -= mod);
		}
		ans = 1LL * sum * pre % mod;
		sum = 0;
		for(int i = 0; i < m; ++i) {
			scanf("%d", &x);
			(sum += x) >= mod && (sum -= mod);
		}
		ans = (ans + 1LL * sum * cur) % mod;
		ans = 1LL * ans * m % mod;
		printf("%d\n", ans);
	}
	return 0;
}
