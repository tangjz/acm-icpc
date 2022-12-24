#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 501, maxd = maxn << 1 | 1;
int n, m, mod, o, f[2][maxd], iact[maxd], pre[maxd], suf[maxd];
int main() {
	scanf("%d%d%d", &m, &n, &mod);
	int upp = min(n << 1, m);
	for(int i = 0; i <= upp; ++i)
		f[o][i] = 1;
	for(int i = 1; i <= n; ++i) {
		o = !o;
		f[o][0] = 0;
		for(int j = 1; j <= upp; ++j)
			f[o][j] = (f[o][j - 1] + (LL)f[!o][j - 1] * j) % mod;
	}
	int ans = 0;
	if(m <= upp) {
		ans = f[o][m];
	} else {
		iact[1] = 1;
		for(int i = 2; i <= upp; ++i)
			iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
		for(int i = 0; i <= upp; ++i)
			pre[i] = suf[i] = m - i;
		iact[0] = 1;
		for(int i = 1; i <= upp; ++i) {
			iact[i] = (LL)iact[i - 1] * iact[i] % mod;
			pre[i] = (LL)pre[i - 1] * pre[i] % mod;
		}
		for(int i = upp - 1; i >= 0; --i)
			suf[i] = (LL)suf[i] * suf[i + 1] % mod;
		for(int i = 0; i <= upp; ++i) {
			int tmp = f[o][i];
			if(i > 0)
				tmp = (LL)tmp * iact[i] % mod * pre[i - 1] % mod;
			if(i < upp)
				tmp = (LL)tmp * iact[upp - i] % mod * suf[i + 1] % mod;
			if(tmp && (upp - i) & 1)
				tmp = mod - tmp;
			(ans += tmp) >= mod && (ans -= mod);
		}		
	}
	for(int i = 2; i <= n; ++i)
		ans = (LL)ans * i % mod;
	printf("%d\n", ans);
	return 0;
}