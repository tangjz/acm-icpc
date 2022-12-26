#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxl = 25, mod = (int)1e9 + 7;
int n, m, sta[maxl], dif[maxl], cnt[maxl], f[maxn], g[maxn];
char buf[maxn], str[maxn];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	if(n & 1) {
		puts("0");
		return 0;
	}
	for(int i = 1; i <= n >> 1; ++i) {
		str[(i << 1) - 1] = buf[i];
		str[i << 1] = buf[n - i + 1];
	}
	f[0] = 1;
	for(int i = 1; i <= n; ++i) {
		int tp = m, las = -maxn;
		static int tsta[maxl], tdif[maxl], tcnt[maxl];
		m = 0;
		memcpy(tsta + 1, sta + 1, tp * sizeof(int));
		memcpy(tdif + 1, dif + 1, tp * sizeof(int));
		memcpy(tcnt + 1, cnt + 1, tp * sizeof(int));
		for(int j = 1; j <= tp; ++j) {
			if(str[tsta[j]] == str[i]) {
				if(m && dif[m] == tsta[j] - 1 - las) {
					++cnt[m];
				} else {
					sta[++m] = tsta[j] - 1;
					dif[m] = sta[m] - las;
					cnt[m] = 1;
				}
				las = tsta[j] - 1;
			}
			if(tcnt[j] > 1 && str[tsta[j] + tdif[j]] == str[i]) {
				if(m && dif[m] == tsta[j] + tdif[j] - 1 - las) {
					cnt[m] += tcnt[j] - 1;
				} else {
					sta[++m] = tsta[j] + tdif[j] - 1;
					dif[m] = sta[m] - las;
					cnt[m] = tcnt[j] - 1;
				}
				las = tsta[j] + tdif[j] * (tcnt[j] - 1) - 1;
			}
		}
		if(str[i - 1] == str[i]) {
			if(m && i - 2 - las == dif[m]) {
				++cnt[m];
			} else {
				sta[++m] = i - 2;
				dif[m] = sta[m] - las;
				cnt[m] = 1;
			}
			las = i - 2;
		}
		for(int j = 1; j <= m; ++j) {
			int tsta = sta[j], tdif = dif[j], tcnt = cnt[j], tend = tsta + (tcnt - 1) * tdif;
			g[tend] = f[tend];
			if(tcnt > 1)
				mod_inc(g[tend], g[tend - tdif]);
			mod_inc(f[i], g[tend]);
		}
	}
	printf("%d\n", f[n]);
	return 0;
}
