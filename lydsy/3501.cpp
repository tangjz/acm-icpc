#include <cstdio>
#include <cstring>
#include <algorithm>
const int mod = 999999599, maxp = 4, maxv = 7285, pr[maxp] = {2, 13, 5281, 7283};
int sei[maxp], b[maxp][maxv], c[maxv], f[maxv];
void exgcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int t, ex, ans;
long long n, m;
int main() {
	for(int i = 0; i < maxp; ++i) {
		int x, y;
		exgcd((mod - 1) / pr[i], pr[i], x, y);
		sei[i] = (mod - 1) / pr[i] * (x < 0 ? x : x + pr[i]);
		b[i][0] = c[0] = 1;
		for(int j = 1; j <= pr[i]; ++j) {
			int tp = c[0];
			b[i][j] = c[0] = c[j - 1];
			for(int k = 1; k <= j; ++k) {
				(tp += c[k - 1]) >= pr[i] && (tp -= pr[i]);
				std::swap(c[k], tp);
			}
		}
	}
	scanf("%lld%lld", &n, &m);
	ex = 0, ans = 1;
	for(int i = 0; i < maxp; ++i) {
		long long tmp = n;
		memcpy(f, b[i], (pr[i] + 1) * sizeof(int));
		for(int dep = 0; tmp > 0; tmp /= pr[i], ++dep)
			for(int j = 0, rem = tmp % pr[i]; j < rem; ++j) {
				for(int k = 0; k < pr[i]; ++k)
					f[k] = (dep * f[k] + f[k + 1]) % pr[i];
				(f[pr[i]] = f[0] + f[1]) >= pr[i] && (f[pr[i]] -= pr[i]);
			}
		ex = (ex + (long long)sei[i] * f[0]) % (mod - 1);
	}
	for(m %= mod; ex > 0; ex >>= 1, m = m * m % mod)
		(ex & 1) && (ans = ans * m % mod);
	printf("%d\n", ans);
	return 0;
}
