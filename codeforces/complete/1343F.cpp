#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 201;
int t, n, que[maxn][maxn], cnt[maxn], seq[maxn], las[maxn];
bool vis[maxn][maxn];
bool solve(int pos, int fir = -1) {
	if(pos == 1) {
		if(fir == -1) {
			static bool rem[maxn];
			memset(rem + 1, 0, n * sizeof(bool));
			for(int i = 2; i <= n; ++i)
				rem[seq[i]] = 1;
			for(int i = 1; i <= n; ++i)
				if(!rem[i]) {
					fir = i;
					break;
				}
		}
		seq[1] = fir;
		for(int i = 1; i < n; ++i) {
			int dt = las[i] - que[i][0];
			for(int j = 1; j <= que[i][0]; ++j)
				if(!vis[i][seq[dt + j]])
					return 0;
		}
		return 1;
	}
	int u = -1, v = -1;
	for(int i = 1; i <= n; ++i)
		if(cnt[i] == 1 && i != fir) {
			assert(v == -1);
			v = u;
			u = i;
		}
	if(v != -1) {
		if(solve(pos, u))
			return 1;
		if(solve(pos, v))
			return 1;
		return 0;
	}
	if(u == -1)
		return 0;
	seq[pos] = u;
	for(int i = 1; i < n; ++i)
		if(!las[i] && vis[i][u]) {
			las[i] = pos;
			for(int j = 1; j <= que[i][0]; ++j)
				--cnt[que[i][j]];
			if(solve(pos - 1, fir))
				return 1;
			for(int j = 1; j <= que[i][0]; ++j)
				++cnt[que[i][j]];
			las[i] = 0;
		}
	return 0;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		memset(cnt + 1, 0, n * sizeof(int));
		for(int i = 1; i < n; ++i) {
			scanf("%d", que[i] + 0);
			memset(vis[i] + 1, 0, n * sizeof(bool));
			for(int j = 1; j <= que[i][0]; ++j) {
				scanf("%d", que[i] + j);
				++cnt[que[i][j]];
				vis[i][que[i][j]] = 1;
			}
		}
		memset(las + 1, 0, n * sizeof(int));
		assert(solve(n));
		for(int i = 1; i <= n; ++i)
			printf("%d%c", seq[i], " \n"[i == n]);
	}
	return 0;
}
