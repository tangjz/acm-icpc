#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
#define x first
#define y second
const int maxn = (int)1e3 + 1, maxd = 26, mod = (int)1e9 + 7;

int main() {
	int t = 1;
	// scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int n, m;
		scanf("%d%d", &n, &m);
		static char buf[maxn][maxn];
		bool chk = 1;
		int cntR = 0, cntC = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%s", buf[i]);
			int L = -1, R = -1, cnt = 0;
			for(int j = 0; j < m; ++j)
				if(buf[i][j] == '#') {
					++cnt;
					L = L < 0 ? j : L;
					R = j;
				}
			cntR += !cnt;
			chk &= !cnt || R - L + 1 == cnt;
		}
		for(int i = 0; chk && i < m; ++i) {
			int L = -1, R = -1, cnt = 0;
			for(int j = 0; j < n; ++j)
				if(buf[j][i] == '#') {
					++cnt;
					L = L < 0 ? j : L;
					R = j;
				}
			cntC += !cnt;
			chk &= !cnt || R - L + 1 == cnt;
		}
		if(!chk || (!cntR) != (!cntC)) {
			puts("-1");
			continue;
		}
		function<void(int, int)> dfs = [&](int x, int y) {
			if(x < 0 || x >= n || y < 0 || y >= m || buf[x][y] != '#')
				return;
			buf[x][y] = '.';
			dfs(x - 1, y);
			dfs(x, y - 1);
			dfs(x, y + 1);
			dfs(x + 1, y);
		};
		int ans = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(buf[i][j] == '#') {
					++ans;
					dfs(i, j);
				}
		printf("%d\n", ans);
	}
	return 0;
}