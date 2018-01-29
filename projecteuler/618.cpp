#include <bits/stdc++.h>
using namespace std;
const int maxk = 25, maxn = 46369, mod = (int)1e9;
int fib[maxk], tot, pr[maxn], d[maxn], f[maxn];
int main() {
	f[0] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			for(int j = i; j < maxn; ++j)
				f[j] = (f[j] + (long long)f[j - i] * i) % mod;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int ans = 0;
	fib[1] = 1;
	for(int i = 2; i < maxk; ++i) {
		fib[i] = fib[i - 2] + fib[i - 1];
		(ans += f[fib[i]]) >= mod && (ans -= mod);
	}
	printf("%d\n", ans);
	return 0;
}
