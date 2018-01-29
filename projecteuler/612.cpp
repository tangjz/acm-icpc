#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 21, maxs = 1 << 10 | 1, mod = 1000267129;
int len, msk[maxn], f[maxs], g[maxs], ans;
char num[maxn];
void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
void mod_dec(int &x, int y) {
	(x -= y) < 0 && (x += mod);
}
int main() {
	LL n;
	while(scanf("%lld", &n) == 1) {
		len = sprintf(num, "%lld", n);
		msk[len - 1] = 0;
		for(int i = len - 1; i > 0; --i)
			msk[i - 1] = msk[i] | 1 << (num[len - i - 1] - '0');
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		f[0] = 1;
		for(int i = 0; i < len; ++i) {
			for(int j = 0; j < 1 << 10; j += 2) {
				mod_inc(g[j], f[j]);
				mod_dec(g[j | 1], f[j]);
			}
			for(int j = 0; j + '0' < num[len - i - 1]; ++j) {
				int mask = msk[i] | 1 << j;
				for(int k = 0; k < 1 << 10; ++k)
					mod_inc(g[mask | k], f[k]);
			}
			for(int j = (1 << 10) - 1; j >= 0; --j) {
				int pre = f[j];
				f[j] = 0;
				for(int k = 0; k < 10; ++k)
					if(j & (1 << k)) {
						mod_inc(f[j], f[j ^ (1 << k)]);
						mod_inc(f[j], pre);
					}
			}
		}
		ans = (n - 1) % mod * ((n - 2) % mod) % mod;
		for(int i = 1; i < 1 << 10; ++i)
			for(int rem = (1 << 10) - 1 - i, j = rem; j; j = (j - 1) & rem)
				ans = (ans - (LL)g[i] * g[j]) % mod;
		ans = (LL)(ans + mod) * ((mod + 1) >> 1) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
