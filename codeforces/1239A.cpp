#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 9, mod = (int)1e9 + 7;
int n, m, fib[maxn];
int main() {
	scanf("%d%d", &n, &m);
	fib[1] = 1;
	for(int i = 1; i <= n || i <= m; ++i)
		fib[i + 1] = (fib[i] + fib[i - 1]) % mod;
	int ans = (fib[n + 1] + fib[m + 1] - 1LL) * 2 % mod;
	printf("%d\n", ans < 0 ? ans + mod : ans);
	return 0;
}