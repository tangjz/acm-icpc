#include <bits/stdc++.h>
using namespace std;
const int maxn = 401;
int n, r, c, match[maxn];
bool e[maxn][maxn], vis[maxn];
bool path(int u) {
	for(int v = 1; v <= n; ++v) {
		if(vis[v] || !e[u][v])
			continue;
		vis[v] = 1;
		if(match[v] == -1 || path(match[v])) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}
int main() {
	long long ans = 0;
	scanf("%d%d", &r, &c);
	if(r >= 20) {
		int adt = (r - 20 + 5) / 6;
		ans += 6LL * adt * c;
		r -= adt * 6;
	}
	if(c >= 20) {
		int adt = (c - 20 + 5) / 6;
		ans += 6LL * adt * r;
		c -= adt * 6;
	}
	n = r * c;
	memset(e, 0, sizeof e);
	for(int i = 0; i < n; ++i) {
		int ix = i / c, iy = i % c;
		if((ix & 1) != (iy & 1))
			continue;
		for(int j = 0; j < n; ++j) {
			int jx = j / c, jy = j % c;
			if((jx & 1) == (jy & 1))
				continue;
			e[i][j] = abs(ix - jx) + abs(iy - jy) == 3;
		}
	}
	memset(match, -1, n * sizeof(int));
	for(int i = 0; i < n; ++i) {
		int ix = i / c, iy = i % c;
		if((ix & 1) != (iy & 1))
			continue;
		memset(vis, 0, n * sizeof(bool));
		if(path(i))
			ans += 2;
	}
	printf("%I64d\n", ans);
	return 0;
}
