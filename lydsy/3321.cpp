#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 7;
inline int mod_pow(int x, LL k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	printf("%d\n", (int)((LL)mod_pow(n, n - 2) * mod_pow(n - 1, (m - 1LL) * n) % mod * mod_pow(m, (LL)n * m - 2) % mod));
	return 0;
}