#include <bits/stdc++.h>
const int maxn = (int)1e5 + 1;
int n, m, s[maxn];
int main() {
	int x, y;
	scanf("%d%d%d", &n, &m, &x);
	for(int i = 1; i < n; ++i) {
		scanf("%d", &y);
		s[i] = s[i - 1] + (-1 <= x - y && x - y <= 1);
		x = y;
	}
	while(m--) {
		scanf("%d%d", &x, &y);
		puts(s[y - 1] - s[x - 1] == (y - x) ? "YES" : "NO");
	}
	return 0;
}
