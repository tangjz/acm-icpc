#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, ans;
bool row[maxn], col[maxn];
int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		row[x] = col[y] = 1;
	}
	for(int i = 1; i <= n; ++i) {
		!row[i] && (++ans);
		!col[i] && (++ans);
	}
	(n & 1) && !row[(n + 1) >> 1] && !col[(n + 1) >> 1] && (--ans);
	printf("%d\n", ans);
	return 0;
}
