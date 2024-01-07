#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 11;
int n, mod, f[maxn];
inline int sum2(int x) {
	return x * (x - 1LL) / 2 % mod;
}
int main() {
	while(scanf("%d%d", &n, &mod) == 2) {
		f[1] = 0;
		f[0] = f[2] = 1 % mod;
		for(int i = 3; i <= n; ++i) {
			f[i] = ((i - 1LL) * (f[i - 1] + f[i - 2]) - (LL)sum2(i - 1) * f[i - 3]) % mod;
			f[i] < 0 && (f[i] += mod);
		}
		printf("%d\n", f[n]);
	}
	return 0;
}
