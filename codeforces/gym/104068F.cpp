#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e6 + 1, mod = 998244353;

int f[maxn];

void prepare() {
	f[0] = f[1] = 1;
	for(int i = 2; i < maxn; ++i)
		f[i] = f[i - 1] * (i + i - 1LL) % mod;
}

void solve() {
	static int n;
	scanf("%d", &n);
	printf("%d\n", f[n - 2]);
}

int main() {
	prepare();

	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
