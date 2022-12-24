#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 37, maxs = 361;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, L, len, cur, pre = 1;
pair<char, int> a[maxn];
LL m, c[maxs][maxs], d[maxs][maxs], f[2][maxs];
char ans[maxs];
int main() {
	for(int i = 0; i < maxs; ++i)
		for(int j = 0; j <= i; ++j) {
			c[i][j] = min(j ? c[i - 1][j - 1] + c[i - 1][j] : 1, INF);
			d[i][j] = INF / c[i][j];
		}
	while(scanf("%d%lld%d", &n, &m, &L) == 3) {
		int mx = 0;
		for(int i = 0; i < n; ++i) {
			char buf[3];
			scanf("%s%d", buf, &a[i].second);
			a[i].first = buf[0];
			mx += a[i].second;
		}
		sort(a, a + n);
		for(len = 0; len < mx && m; ++len) {
			for(int i = n - 1; i >= 0; --i) {
				if(!a[i].second)
					continue;
				ans[len] = a[i].first;
				--a[i].second;
				int psz, csz = 1;
				f[cur][0] = 1;
				for(int j = 0; j < n; ++j) {
					if(!a[j].second)
						continue;
					pre ^= 1;
					cur ^= 1;
					psz = csz;
					csz += a[j].second;
					memset(f[cur], 0, csz * sizeof(LL));
					for(int k = 0; k < psz; ++k)
						for(int x = k, y = 0; y <= a[j].second; ++x, ++y)
							f[cur][x] = min(f[cur][x] + (f[pre][k] <= d[x][y] ? f[pre][k] * c[x][y] : INF), INF);
				}
				LL ways = 0;
				for(int j = max(L - len - 1, 0); j < csz; ++j)
					ways = min(ways + f[cur][j], INF);
				if(m <= ways) {
					if(len >= L - 1 && m == ways)
						m = 0;
					break;
				}
				m -= ways;
				ans[len] = '\0';
				++a[i].second;
			}
			if(m && !ans[len])
				break;
		}
		ans[len] = '\0';
		puts(m ? "-1" : ans);
	}
	return 0;
}