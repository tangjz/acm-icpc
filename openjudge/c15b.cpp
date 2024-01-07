#include <bits/stdc++.h>

const int maxn = (int)1e3 + 1;

void solve() {
	int n, m;
	static int a[maxn], b[maxn];
	static char buf[maxn];
	scanf("%d%d", &m, &n);
	memset(a, 0, n * sizeof(int));
	for(int i = 0; i < m; ++i) {
		scanf("%s", buf);
		for(int j = 0; j < n; ++j)
			if(buf[j] == '#')
				a[j] = (a[j] + 1) & 3;
	}
	b[0] = 0;
	for(int i = 1; i < n - 3; ++i)
		b[i] = (a[i - 1] - a[i] + (i >= 4 ? b[i - 4] : 0)) & 3;
	for(int i = n - 3; i < n; ++i)
		if((i & 3) && ((a[i - 1] - a[i] + b[i - 4]) & 3)) {
			puts("NO");
			return;
		}
	puts("YES");
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
