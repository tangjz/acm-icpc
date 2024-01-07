#include <bits/stdc++.h>
using namespace std;
const int maxn = 201;
int t, n, r, c, wan[maxn][maxn];
bool vis[maxn][maxn];
set<pair<int, int> > pos[11];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		memset(wan, 0, sizeof wan);
		memset(vis, 0, sizeof vis);
		for(int i = 0; i <= 9; ++i)
			set<pair<int, int> >().swap(pos[i]);
		n = max(n, 9);
		r = 3;
		c = (n - 1) / r + 1;
		for(int i = 4, j; (j = (n - 1) / i + 1) >= 3; ++i)
			if(i * j < r * c) {
				r = i;
				c = j;
			}
		for(int i = 1; i <= r; ++i)
			for(int j = 1; j <= c; ++j)
				for(int dx = -1; dx <= 1; ++dx)
					for(int dy = -1; dy <= 1; ++dy) {
						int x = i + dx, y = j + dy;
						if(x > 1 && x < r && y > 1 && y < c)
							++wan[x][y];
					}
		for(int i = 2; i < r; ++i)
			for(int j = 2; j < c; ++j)
				pos[wan[i][j]].insert(make_pair(i, j));
		int mx = 9;
		while(1) {
			for( ; !pos[mx].size(); --mx);
			assert(mx > 0);
			pair<int, int> state = *pos[mx].begin();
			int x = state.first, y = state.second;
			printf("%d %d\n", x, y);
			fflush(stdout);
			scanf("%d%d", &x, &y);
			if(x <= 0 || y <= 0)
				break;
			if(vis[x][y])
				continue;
			vis[x][y] = 1;
			for(int dx = -1; dx <= 1; ++dx)
				for(int dy = -1; dy <= 1; ++dy) {
					int xx = x + dx, yy = y + dy;
					if(xx > 1 && xx < r && yy > 1 && yy < c) {
						pos[wan[xx][yy]].erase(make_pair(xx, yy));
						pos[--wan[xx][yy]].insert(make_pair(xx, yy));
					}
				}
		}
	}
	return 0;
}
