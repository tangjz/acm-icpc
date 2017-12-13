#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = (int)1e9 + 7;
int t, n, m, f[maxn];
LL s[maxn];
int main() {
	for(int i = 1; i < maxn; ++i)
		s[i] = s[i - 1] + i;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		f[m] = 1;
		for(int i = 1; s[i] << 1 < s[m]; ++i)
			(f[m] <<= 1) >= mod && (f[m] -= mod);
		if(m < n) {
			int L = m + 1, R = m + 1, sum = 0; // [L, R)
			for( ; L > m && s[L - 1] << 1 >= s[R]; (sum += f[--L]) >= mod && (sum -= mod));
			for( ; R <= n; (sum += f[R++]) >= mod && (sum -= mod)) {
				for( ; s[L] << 1 < s[R]; (sum -= f[L++]) < 0 && (sum += mod));
				f[R] = sum;
			}
		}
		(f[n] <<= 1) >= mod && (f[n] -= mod);
		printf("Case #%d: %d\n", Case, f[n]);
	}
	return 0;
}
