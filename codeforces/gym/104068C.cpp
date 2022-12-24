#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

void solve() {
	int n, r, s;
	scanf("%d%d", &n, &r);
	while(n--) {
		scanf("%d", &s);
		s += r * 3;
		r = min(r, (s + (-s & 3)) >> 2);
	}
	printf("%d\n", r);
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