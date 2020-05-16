#include <bits/stdc++.h>
using namespace std;
int n, d, m, x, y;
int main() {
	scanf("%d%d%d", &n, &d, &m);
	while(m--) {
		scanf("%d%d", &x, &y);
		puts(d <= x + y && x + y <= n + n - d && abs(x - y) <= d ? "YES" : "NO");
	}
	return 0;
}
