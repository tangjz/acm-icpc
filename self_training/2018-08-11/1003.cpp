#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e4 + 1;
int n, m, tot, f[maxn], g[maxn];
pair<char, int> seq[maxn];
char buf[maxn];
int main() {
	while(scanf("%d%d%s", &n, &m, buf) == 3) {
		tot = 0;
		for(int i = 0; i < n; ++i)
			if(!tot || buf[i] != seq[tot - 1].first)
				seq[tot++] = make_pair(buf[i], 1);
			else
				++seq[tot - 1].second;
		memset(f, 0, (m + 1) * sizeof(int));
		memset(g, 0, (m + 1) * sizeof(int));
		{
			bool fir = 0;
			f[0] = seq[0].first == '1' ? seq[0].second : 0;
			if(seq[0].first == '1')
				fir = 1;
			if(tot > 2) {
				sort(seq + 1, seq + tot - 1);
				for(int i = tot - 2, j = 0; i > 0 && j + 1 + fir <= m; --i)
					if(seq[i].first == '1') {
						f[j + 1 + fir] = f[j] + seq[i].second;
						j += 1 + fir;
						fir = 1;
					}
			}
			for(int i = 1; i <= m; ++i)
				f[i] = max(f[i], f[i - 1]);
		}
		{
			bool fir = 0;
			g[0] = 0;
			if(tot > 2) {
				sort(seq + 1, seq + tot - 1);
				for(int i = tot - 2, j = 0; i > 0 && j + 1 + fir <= m; --i)
					if(seq[i].first == '1') {
						g[j + 1 + fir] = g[j] + seq[i].second;
						j += 1 + fir;
						fir = 1;
					}
			}
			for(int i = 1; i <= m; ++i)
				g[i] = max(g[i], g[i - 1]);
		}
		int ans = max(f[m], g[m]);
		if(tot > 1 && seq[tot - 1].first == '1' && m > 0)
			ans = max(ans, max(f[m - 1], g[m - 1]) + seq[tot - 1].second);
		printf("%d\n", ans);
	}
	return 0;
}
