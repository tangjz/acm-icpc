#include <bits/stdc++.h>
using namespace std;
int n, ans, mod = (int)1e9 + 9;
int main() {
	scanf("%d", &n);
	ans = 1;
	for(int i = 1; i < n; ++i)
		ans = ans * (i << 1 | 1LL) % mod;
	printf("%d\n", ans);
	return 0;
}
