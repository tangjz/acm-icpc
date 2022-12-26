#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1, maxd = 10;

void solve() {
	int n, m;
	static int ctr[maxd | 1];
	static char buf[maxn];
	scanf("%d%d", &n, &m);
	for(int i = 1; i < maxd; ++i)
		scanf("%d", ctr + i);
	for(int i = maxd - 1, j = n; i > 0; --i)
		for( ; ctr[i]--; --j)
			if(j > 0) {
				buf[j - 1] = '0' + i;
			} else {
				buf[-j] -= i;
			}
	for( ; n > 1 && buf[n - 1] == '0'; --n);
	reverse(buf, buf + n);
	buf[n] = '\0';
	puts(buf);
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
