#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 501, maxm = 1001, maxt = 21, seq[maxt] = {999999487,
999999491, 999999503, 999999527, 999999541, 999999587,
999999599, 999999607, 999999613, 999999667, 999999677,
999999733, 999999739, 999999751, 999999757, 999999761,
999999797, 999999883, 999999893, 999999929, 999999937};
int t, n, a[maxn], mx, pw[maxn], f[maxm];
bool g[maxm];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		mx = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			mx < a[i] && (mx = a[i]);
		}
		memset(g + 1, 0, mx * sizeof(bool));
		for(int o = 0; o < maxt; ++o) {
			int mod = seq[o];
			memset(f + 1, 0, mx * sizeof(int));
			pw[0] = 1;
			for(int i = 1; i <= n; ++i) {
				++f[a[i]];
				(pw[i] = pw[i - 1] << 1) >= mod && (pw[i] -= mod);
			}
			for(int i = 1; i <= mx; ++i)
				for(int j = i + i; j <= mx; j += i)
					f[i] += f[j];
			for(int i = mx; i >= 1; --i) {
				f[i] = pw[f[i]] - 1;
				for(int j = i + i; j <= mx; j += i)
					(f[i] -= f[j]) < 0 && (f[i] += mod);
			}
			int r = 0;
			for(int i = 1; i <= n; ++i) {
				(--f[a[i]]) < 0 && (f[a[i]] += mod);
				r = std::__gcd(r, a[i]);
			}
			(--f[r]) < 0 && (f[r] += mod);
			for(int i = 1; i <= mx; ++i)
				g[i] |= f[i] > 0;
		}
		for(int i = 1, p = 0; i <= mx; ++i) {
			if(!g[i])
				continue;
			if(p)
				putchar(' ');
			printf("%d", p = i);
		}
		putchar('\n');
	}
	return 0;
}
