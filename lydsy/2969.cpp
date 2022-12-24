#include <bits/stdc++.h>
using namespace std;
typedef long double LD;
typedef long long LL;
int main() {
	int n, m, k;
	scanf("%d%d%d", &k, &n, &m);
	LD ans = 0, all = n * n * m * (LL)m;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			int row = (i + 1) * (n - i), col = (j + 1) * (m - j);
			LD prb = 1 - (row + row - 1) * (col + col - 1LL) / all;
			ans += 1 - pow(prb, k);
		}
	printf("%.0f\n", (double)ans);
	return 0;
}