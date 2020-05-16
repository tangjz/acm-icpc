#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, k, las, ans;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	las = 0;
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		ans += (x - las) / k;
		las = x + y;
	}
	ans += (m - las) / k;
	printf("%d\n", ans);
	return 0;
}
