#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = (int)3e5 + 9, maxm = 31;
int n, f[2][maxm], cur, pre = 1;
int main() {
	scanf("%d", &n);
	memset(f[cur], 0x3f, sizeof f[0]);
	f[cur][0] = 0;
	for(int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		x /= 100;
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], 0x3f, sizeof f[0]);
		for(int j = 0; j < maxm; ++j)
			for(int k = 1; k <= x && j + k < maxm; ++k)
				f[cur][j] = min(f[cur][j], f[pre][j + k] + x - k);
		int y = x / 10;
		for(int j = y; j < maxm; ++j)
			f[cur][j] = min(f[cur][j], f[pre][j - y] + x);
	}
	int ans = f[cur][0];
	for(int i = 1; i < maxm; ++i)
		ans = min(ans, f[cur][i]);
	printf("%d\n", ans * 100);
	return 0;
}
