#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = 11;
int n, m, a[maxm][maxn], pos[maxm][maxn];
LL f[maxn], ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= n; ++j) {
			scanf("%d", a[i] + j);
			pos[i][a[i][j]] = j;
		}
	for(int i = 1; i <= n; ++i) {
		f[i] = 1;
		bool chk = i > 1;
		int val = a[1][i - 1];
		for(int j = 1; chk && j <= m; ++j)
			chk &= val == a[j][pos[j][a[1][i]] - 1];
		if(chk)
			f[i] += f[i - 1];
		ans += f[i];
	}
	printf("%lld\n", ans);
	return 0;
}