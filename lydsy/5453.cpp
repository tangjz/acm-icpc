#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = 998244353;
int n, a[maxn], d[maxn], p[maxn], c[2];
int solve() {
	if(n & 1)
		return 0;
	for(int i = 1; i <= n; ++i) {
		++d[a[i]];
		int j, ctr = 0;
		for(j = i; j && !p[j]; j = a[j], ++ctr)
			p[j] = -1;
		if(j == i && (ctr & 1))
			return 0;
	}
	for(int i = 1; i <= n; ++i) {
		if(d[i] == 1)
			continue;
		int ctr = 0;
		for(int j = i; j; j = a[j], ++ctr);
		++c[ctr & 1];
	}
	int ans = 1;
	for(int i = 0; i < c[1]; ++i)
		ans = (LL)ans * (i | 1) % mod;
	for(int i = 1; i <= c[0]; ++i)
		ans = (LL)ans * (c[1] + i) % mod;
	return ans;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	printf("%d\n", solve());
	return 0;
}
