#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 21;

void solve() {
	int n, m = 0;
	static int a[maxn], ord[maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		if(a[i] != -1) {
			ord[m++] = i;
		}
	}
	int low = a[ord[0]], com = 0;
	for(int i = 1; i < m; ++i) {
		int u = ord[i - 1], v = ord[i];
		int stp = v - u, dt = a[v] - a[u];
		if(stp < dt) {
			puts("impossible");
			return;
		}
		low = max(low, a[v]);
		if(stp > dt) {
			com = gcd(com, stp - dt);
		}
	}
	if(!com) {
		puts("inf");
		return;
	}
	if(low > com) {
		puts("impossible");
		return;
	}
	printf("%d\n", com);
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