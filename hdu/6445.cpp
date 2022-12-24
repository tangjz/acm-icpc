#include <bits/stdc++.h>
using namespace std;
const int maxn = 201;
int t, n, deg[maxn], rem[maxn];
char buf[maxn][maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			scanf("%s", buf[i]);
			deg[i] = rem[i] = 0;
			for(int j = 0; j < n; ++j)
				if(buf[i][j] == '1')
					++deg[i];
				else if(buf[i][j] == '2')
					++rem[i];
		}
		while(1) {
			int u = -1;
			for(int i = 0; i < n; ++i)
				if(rem[i] && (u == -1 || deg[i] > deg[u]))
					u = i;
			if(u == -1)
				break;
			int v = -1;
			for(int i = 0; i < n; ++i)
				if(buf[u][i] == '2' && (v == -1 || deg[i] < deg[v]))
					v = i;
			buf[u][v] = '0';
			buf[v][u] = '1';
			++deg[v];
			--rem[u];
			--rem[v];
		}
		int ans = 0;
		for(int i = 0; i < n; ++i) {
			int x = deg[i], y = n - 1 - x;
			ans += x * y - x * (x - 1) / 2 - y * (y - 1) / 2;
		}
		ans *= (n - 3) * 2;
		printf("%d\n", ans);
	}
	return 0;
}
