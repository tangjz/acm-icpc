#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 31, maxd = 26;
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int r, c;
		static char buf[maxn][maxn];
		static bool vis[maxd + 1], e[maxd + 1][maxd + 1];
		static int deg[maxd + 1];
		for(int i = 0; i < maxd; ++i) {
			vis[i] = 0;
			for(int j = 0; j < maxd; ++j)
				e[i][j] = 0;
			deg[i] = 0;
		}
		scanf("%d%d", &r, &c);
		int cnt = 0;
		for(int i = 0; i < r; ++i) {
			scanf("%s", buf[i]);
			for(int j = 0; j < c; ++j) {
				int u = buf[i][j] - 'A';
				cnt += !vis[u];
				vis[u] = 1;
			}
		}
		for(int i = 0; i + 1 < r; ++i)
			for(int j = 0; j < c; ++j)
				if(buf[i][j] != buf[i + 1][j]) {
					int u = buf[i + 1][j] - 'A';
					int v = buf[i][j] - 'A';
					if(e[u][v])
						continue;
					e[u][v] = 1;
					++deg[v];
				}
		int tot = 0;
		static char out[maxd + 1];
		for(int i = 0; i < maxd; ++i)
			if(vis[i] && !deg[i])
				out[tot++] = 'A' + i;
		for(int i = 0; i < tot; ++i) {
			int u = out[i] - 'A';
			for(int v = 0; v < maxd; ++v)
				if(e[u][v] && !(--deg[v]))
					out[tot++] = 'A' + v;
		}
		if(tot < cnt) {
			printf("Case #%d: -1\n", Case);
		} else {
			out[tot] = '\0';
			printf("Case #%d: %s\n", Case, out);
		}
	}
	return 0;
}