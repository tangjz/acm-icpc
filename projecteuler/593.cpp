#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxp = 179424675, maxn = (int)1e7 + 1, mod = (int)1e4 + 7, DELTA = (int)1e4, maxm = 20013, mx = 1 << 14;
int tot, pr[maxn], d[maxp], s[2][maxn], bit[maxm];
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
void bit_add(int x, int v) {
	for( ; x < maxm; x += x & -x)
		bit[x] += v;
}
int bit_que(int k) {
	int x = 0;
	for(int y = mx, z; y; y >>= 1)
		if((z = x | y) < maxm && bit[z] < k) {
			x = z;
			k -= bit[x];
		}
	return x + 1;
}
int main() {
	for(int i = 2; i < maxp; ++i) {
		if(!d[i]) {
			pr[++tot] = d[i] = i;
			s[0][tot] = mod_pow(i, tot);
			s[1][tot] = s[0][tot] + s[0][tot / DELTA + 1];
		}
		LL k;
		for(int j = 1; (k = (LL)i * pr[j]) < maxp; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int n, m;
	while(scanf("%d%d", &n, &m) == 2) {
		LL ans = 0;
		memset(bit, 0, sizeof bit);
		for(int i = 1; i < m; ++i)
			bit_add(s[1][i], 1);
		for(int i = m; i <= n; ++i) {
			bit_add(s[1][i], 1);
			LL las = ans;
			ans += bit_que((m + 1) >> 1) + bit_que((m + 2) >> 1);
			bit_add(s[1][i - m + 1], -1);
		}
		printf("%lld.%c\n", ans >> 1, "05"[ans & 1]);
	}
	return 0;
}
