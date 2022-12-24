#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

void solve() {
	int x, y;
	scanf("%d%d", &x, &y);
	printf("%.7f\n", x / (y + (double)1));
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