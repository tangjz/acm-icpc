#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 101;
int n, m, a[maxn][maxn], r[maxn], c[maxn];
long long ans;
int e[maxn][maxn], match[maxn];
bool vis[maxn];
bool path(int u) {
	for(int i = 1; i <= e[u][0]; ++i) {
		int v = e[u][i];
		if(!vis[v]) {
			vis[v] = 1;
			if(match[v] == -1 || path(match[v])) {
				match[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			scanf("%d", a[i] + j);
			if(!a[i][j])
				continue;
			r[i] = max(r[i], a[i][j]);
			c[j] = max(c[j], a[i][j]);
			ans += a[i][j] - 1;
		}
	memset(match, -1, m * sizeof(int));
	for(int i = 0; i < n; ++i) {
		if(!r[i])
			continue;
		for(int j = 0; j < m; ++j) {
			if(!a[i][j] || r[i] != c[j])
				continue;
			e[i][++e[i][0]] = j;
		}
		memset(vis, 0, m * sizeof(bool));
		if(path(i))
			ans += r[i] - 1;
	}
	for(int i = 0; i < n; ++i)
		if(r[i])
			ans -= r[i] - 1;
	for(int j = 0; j < m; ++j)
		if(c[j])
			ans -= c[j] - 1;
	printf("%lld\n", ans);
	return 0;
}