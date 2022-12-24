#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 21, maxd = 1 << 20 | 1, maxs = (int)1e5 + 1, maxc = 27;
int n, nxt[maxn][maxc];
LL f[maxd][maxc];
char buf[maxs];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf);
		int *vec = nxt[i];
		for(int j = 0; j < maxc; ++j)
			vec[j] = j;
		for(int j = 0; buf[j]; ++j) {
			int o = buf[j] - 'a';
			for(int j = 0; j < maxc; ++j)
				vec[j] = vec[j] == o ? maxc - 1 : (vec[j] == maxc - 1 ? o : vec[j]);
		}
	}
	f[0][maxc - 1] = 1;
	for(int i = 1; i < 1 << n; ++i)
		for(int j = 0; j < n; ++j)
			if((i >> j) & 1) {
				int *vec = nxt[j], ii = i ^ (1 << j);
				for(int k = 0; k < maxc; ++k)
					f[i][vec[k]] += f[ii][k];
			}
	LL ans = 0;
	for(int i = 0; i < maxc - 1; ++i)
		ans += f[(1 << n) - 1][i];
	printf("%lld\n", ans);
	return 0;
}