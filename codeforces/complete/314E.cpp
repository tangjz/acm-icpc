#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, f[maxn];
char buf[maxn];
int main() {
	scanf("%d%s", &n, buf);
	if(n & 1) {
		puts("0");
		return 0;
	}
	f[0] = 1;
	for(int i = 1; i <= n; ++i) {
		int upp = i >> 1;
		if(buf[i - 1] != '?') {
			++m;
		} else {
			int low = max(i - (n >> 1), 0);
			upp = min(upp, i - m);
			for( ; low <= upp; --upp)
				f[upp] += f[upp - 1];
		}
	}
	int ans = f[n >> 1];
	for(int i = m + m; i < n; i += 2)
		ans *= 25;
	printf("%u\n", ans);
	return 0;
}