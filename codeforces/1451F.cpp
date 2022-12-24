#include <bits/stdc++.h>
using namespace std;

const int maxn = 101;

void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> f(n + m - 1);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			int x;
			scanf("%d", &x);
			f[i + j] ^= x;
		}
	for(int x: f)
		if(x) {
			puts("Ashish");
			return;
		}
	puts("Jeel");
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
