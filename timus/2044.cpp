#include <bits/stdc++.h>
using namespace std; 
const int maxn = (int)3e5 + 3, maxl = 25, BLEN = 31, BMSK = 0x7FFFFFFF, S = 0x55555555;
int n, m, f[2][maxn], g[2][maxn];
char str[maxn];
struct Border {
	int fir, dif, las;
} seq[maxl];
inline void append(int pL, int pR) {
	int dif = pL - seq[m].las;
	if(m && dif == seq[m].dif)
		seq[m].las = pR;
	else
		seq[++m] = (Border){pL, dif, pR};
}
inline void upd(int &x, int y) {
	x > y && (x = y);
}
int main() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	seq[0].las = -maxn;
	f[1][0] = maxn;
	for(int i = 1; i <= n; ++i) {
		int sz = m;
		static Border tmp[maxl];
		memcpy(tmp + 1, seq + 1, sz * sizeof(Border));
		m = 0;
		for(int j = 1; j <= sz; ++j) {
			if(str[tmp[j].fir] == str[i])
				append(tmp[j].fir - 1, tmp[j].fir - 1);
			if(tmp[j].fir != tmp[j].las && str[tmp[j].las] == str[i])
				append(tmp[j].fir + tmp[j].dif - 1, tmp[j].las - 1);
		}
		if(str[i - 1] == str[i])
			append(i - 2, i - 2);
		append(i - 1, i - 1);
		f[0][i] = f[1][i] = maxn;
		for(int j = 1; j <= m; ++j) {
			int pos = seq[j].las;
			g[0][pos] = f[1][pos] + 1;
			g[1][pos] = f[0][pos] + 1;
			if(seq[j].fir != seq[j].las) {
				upd(g[0][pos], g[0][pos - seq[j].dif]);
				upd(g[1][pos], g[1][pos - seq[j].dif]);
			}
			upd(f[0][i], g[0][pos]);
			upd(f[1][i], g[1][pos]);
		}
		int res = 0;
		if(f[0][i] <= BLEN)
			res |= S << f[0][i];
		if(f[1][i] <= BLEN)
			res |= S << f[1][i];
		res = (res >> 1) & (i < BLEN ? (1 << i) - 1 : BMSK);
		printf("%d\n", res);
	}
	return 0;
}
