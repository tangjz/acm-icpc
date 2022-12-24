#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1, mod = (int)1e9 + 7;
int f[maxn][maxn];
int main() {
	for(int i = 1; i < maxn; ++i) {
		f[i][0] = 1;
		for(int j = 1; j < i; ++j)
			f[i][j] = ((LL)(i - j) * f[i - 1][j - 1] + (j + 1LL) * f[i - 1][j]) % mod;
	}
	int n, k;
	while(scanf("%d%d", &n, &k) == 2)
		printf("%d\n", f[n][k]);
	return 0;
}