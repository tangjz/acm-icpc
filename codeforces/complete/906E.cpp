#include <bits/stdc++.h>
using namespace std; 
const int maxn = (int)1e6 + 1, maxl = 25;
int n, m, sta[maxl], dif[maxl], cnt[maxl];
pair<int, int> f[maxn], g[maxn];
char buf[maxn], str[maxn];
int main() {
	scanf("%s%s", buf + 1, str + 1);
	n = strlen(buf + 1);
	for(int i = n; i >= 1; --i) {
		str[(i << 1) - 1] = str[i];
		str[i << 1] = buf[i];
	}
	n <<= 1;
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
			f[i] = make_pair(f[i - 2].first, i - 2);
		} else {
			f[i] = make_pair(maxn, i);
		}
		for(int j = 1; j <= m; ++j) {
			int tsta = sta[j], tdif = dif[j], tcnt = cnt[j], tend = tsta + (tcnt - 1) * tdif;
			g[tend] = make_pair(f[tend].first + 1, tend);
			if(tcnt > 1)
				g[tend] = min(g[tend], g[tend - tdif]);
			f[i] = min(f[i], g[tend]);
		}
	}
	if(f[n].first < maxn) {
		printf("%d\n", f[n].first);
		for(int i = n; i > 0; i = f[i].second)
			if(i - f[i].second > 2)
				printf("%d %d\n", (f[i].second >> 1) + 1, i >> 1);
	} else {
		puts("-1");
	}
	return 0;
}
