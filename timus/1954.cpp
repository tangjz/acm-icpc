#include <bits/stdc++.h>
using namespace std; 
const int maxn = (int)1e5 + 3, maxl = 19;
int n, m;
pair<int, int> f[2][maxn], g[2][maxn];
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
int main() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	seq[0].las = -maxn;
	f[1][0].first = maxn;
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
		f[0][i] = f[1][i] = make_pair(maxn, i);
		for(int j = 1; j <= m; ++j) {
			int pos = seq[j].las;
			g[0][pos] = make_pair(f[1][pos].first + 1, pos);
			g[1][pos] = make_pair(f[0][pos].first + 1, pos);
			if(seq[j].fir != seq[j].las) {
				g[0][pos] = min(g[0][pos], g[0][pos - seq[j].dif]);
				g[1][pos] = min(g[1][pos], g[1][pos - seq[j].dif]);
			}
			f[0][i] = min(f[0][i], g[0][pos]);
			f[1][i] = min(f[1][i], g[1][pos]);
		}
	}
	if(f[1][n].first <= 5) {
		int cnt = 0, pos[maxl] = {};
		for(int i = n, j = 1; i; pos[cnt++] = i, i = f[j][i].second, j = !j);
		while(cnt < 5) {
			int idx;
			for(idx = 0; idx < cnt && pos[idx] - pos[idx + 1] <= 2; ++idx);
			for(int i = cnt - 1; i > idx; --i)
				pos[i + 2] = pos[i];
			pos[idx + 1] = pos[idx] - 1;
			pos[idx + 2] = pos[idx + 3] + 1;
			cnt += 2;
		}
		puts("YES");
		for(int i = cnt - 1; i >= 0; --i) {
			char ch = str[pos[i] + 1];
			str[pos[i] + 1] = '\0';
			puts(str + pos[i + 1] + 1);
			str[pos[i] + 1] = ch;
		}
	} else {
		puts("NO");
	}
	return 0;
}
