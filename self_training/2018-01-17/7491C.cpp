#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 7;
int main() {
	int n, k, ans = 1;
	scanf("%d", &n);
	for(k = (n - 1) * (n - 1); k > 0; k >>= 1, n = (LL)n * n % mod)
		(k & 1) && (ans = (LL)ans * n % mod);
	printf("%d\n", ans);
	return 0;
}
