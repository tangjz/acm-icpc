#include <bits/stdc++.h>
const int maxn = 151, maxc = 27, maxl = 571;
int n, tot, cnt, f[maxn];
char buf[maxn], pat[maxl];
std::bitset<maxl> fst[maxc], mid[maxc], lst[maxc], g[maxn][maxn];
inline void upd(int &x, int y) {
	x > y && (x = y);
}
int main() {
	scanf("%s%d", buf, &tot);
	n = strlen(buf);
	while(tot--) {
		scanf("%s", pat);
		for(int i = 0; pat[i]; ++i) {
			int o = pat[i] - 'a';
			if(!pat[i + 1]) { // last
				lst[o].set(i ? cnt : 0);
			} else if(!i) { // first
				fst[o].set(++cnt);
			} else { // middle
				mid[o].set(++cnt);
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		int o = buf[i] - 'a';
		g[i][i] = fst[o];
		if(lst[o].test(0))
			g[i][i].set(0);
	}
	for(int i = n - 1; i >= 0; --i)
		for(int j = i + 1; j < n; ++j) {
			int o = buf[j] - 'a';
			g[i][j] = (g[i][j - 1] << 1) & mid[o];
			if(g[i][j - 1].test(0))
				g[i][j] |= fst[o];
			if((g[i][j - 1] & lst[o]).any())
				g[i][j].set(0);
			for(int k = i; k < j; ++k)
				if(g[k + 1][j].test(0))
					g[i][j] |= g[i][k];
		}
	for(int i = 1; i <= n; ++i) {
		f[i] = f[i - 1] + 1;
		for(int j = 0; j < i; ++j)
			if(g[j][i - 1].test(0))
				upd(f[i], f[j]);
	}
	printf("%d\n", f[n]);
	return 0;
}