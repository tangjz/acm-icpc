#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 21;

void solve() {
	int n, m;
	static int a[maxn];
	assert(
		scanf("%d%d", &n, &m) == 2
		&& 2 <= n && n <= 10
		&& 1 <= m && m <= 1000
	);
	for(int i = 1; i <= n; ++i) {
		assert(
			scanf("%d", a + i) == 1
			&& m < a[i] && a[i] <= 100000
		);
	}
	if(a[n] >= a[n - 1]) {
		puts("Python will never be faster than C++");
		return;
	}
	for( ; a[n] >= m; ++n) {
		a[n + 1] = a[n] - a[n - 1] + a[n];
	}
	printf("Python 3.%d will be faster than C++\n", n);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
