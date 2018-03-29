#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m, dt, tot, x1, y1, x2, y2, ans = 0;
	scanf("%d%d%d%d%d%d", &n, &m, &dt, &tot, &x1, &y1);
	for(int i = 0; i < m; ++i) {
		scanf("%d%d", &x2, &y2);
		ans = max(ans, tot - dt * ((x1 < x2) == (y1 < y2) ? max(abs(x1 - x2) << 1, abs(y1 - y2)) - (!((x1 - x2) & 1) && ((y1 - y2) & 1)) : (abs(x1 - x2) << 1) + abs(y1 - y2)));
	}
	printf("%d\n", --ans);
	return 0;
}
