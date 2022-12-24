#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const char dig[] = "0123456789ABCDEF";
int t, n;
DB ans;
int mod_pow(int x, int k, int p) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		(k & 1) && (ret = (LL)ret * x % p);
	return ret;
}
inline DB calc(int x, int k, int p) {
	return mod_pow(x, k, p) / (DB)p;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		if(!n) {
			putchar('3');
			continue;
		}
		ans = 0;
		for(int i = 0, j = n - 1; i < n; ++i, --j)
			ans += 4 * calc(16, j, i << 3 | 1) - 2 * calc(16, j, i << 3 | 4) - calc(16, j, i << 3 | 5) - calc(16, j, i << 3 | 6);
		ans -= floor(ans);
		putchar(dig[(int)(ans * 16)]);
	}
	putchar('\n');
	return 0;
}