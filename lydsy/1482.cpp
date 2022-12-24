#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e3 + 3, INF = 0x3f3f3f3f;
int t, n, a[maxn], c[3], f[2][maxn][3][4], cur, pre = 1;
inline void upd(int &x, int y) {
	x > y && (x = y);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		c[0] = c[1] = c[2] = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%d", a + i);
			++c[a[i]];
		}
		if(!c[0] || !c[1]) {
			puts("0");
			continue;
		}
		if(!c[2]) {
			puts("-1");
			continue;
		}
		memset(f[cur], 0x3f, (c[2] + 1) * sizeof(f[0][0]));
		f[cur][0][2][0] = 0;
		for(int i = 0; i < n; ++i) {
			swap(cur, pre);
			memset(f[cur], 0x3f, (c[2] + 1) * sizeof(f[0][0]));
			bool chk = a[i] == 2;
			for(int j = 0; j <= c[2]; ++j)
				for(int x = 0; x < 3; ++x)
					for(int s = 0; s < 4; ++s) {
						if(f[pre][j][x][s] == INF)
							continue;
						// pick, not insert 2
						upd(f[cur][j][x][s], f[pre][j][x][s] + !chk);
						// pick, insert 2
						upd(f[cur][j + 1][2][s], f[pre][j][x][s] + !chk + 1);
						if(x == 2) {
							upd(f[cur][j + 1][2][s | 1], f[pre][j][x][s] + !chk + 1);
							upd(f[cur][j + 1][2][s | 2], f[pre][j][x][s] + !chk + 1);
						}
						int t = chk ? s : s | 1 << a[i];
						// remain, not insert 2
						if(x + a[i] != 1) {
							upd(f[cur][j + chk][a[i]][t], f[pre][j][x][s]);
							if(chk && x == 2) {
								upd(f[cur][j + chk][a[i]][t | 1], f[pre][j][x][s]);
								upd(f[cur][j + chk][a[i]][t | 2], f[pre][j][x][s]);
							}
						}
						// remain, insert 2
						upd(f[cur][j + chk + 1][a[i]][t], f[pre][j][x][s] + 1);
						if(chk || x == 2) {
							upd(f[cur][j + chk + 1][a[i]][t | 1], f[pre][j][x][s] + 1);
							upd(f[cur][j + chk + 1][a[i]][t | 2], f[pre][j][x][s] + 1);
						}
					}
		}
		int ans = INF;
		for(int x = 0; x < 3; ++x)
			for(int s = 0; s < 4; ++s)
				if(s == 3 || (s && x == 2))
					upd(ans, f[cur][c[2]][x][s]);
		printf("%d\n", ans < INF ? ans : -1);
	}
	return 0;
}
