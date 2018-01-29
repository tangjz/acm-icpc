#include <bits/stdc++.h>
const int maxn = 51, maxs = 101, dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};
int n, m, perm[4], sx, sy, ex, ey;
char buf[maxn][maxn], str[maxs];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf[i]);
		for(int j = 0; j < m; ++j)
			if(buf[i][j] == 'S') {
				sx = i;
				sy = j;
			} else if(buf[i][j] == 'E') {
				ex = i;
				ey = j;
			}
	}
	scanf("%s", str);
	int ans = 0;
	for(int i = 0; i < 4; ++i)
		perm[i] = i;
	do {
		int cx = sx, cy = sy;
		bool chk = 0;
		for(int i = 0; str[i]; ++i) {
			int o = perm[str[i] - '0'];
			int nx = cx + dx[o], ny = cy + dy[o];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m || buf[nx][ny] == '#')
				break;
			if(buf[nx][ny] == 'E') {
				chk = 1;
				break;
			}
			cx = nx;
			cy = ny;
		}
		ans += chk;
	} while(std::next_permutation(perm, perm + 4));
	printf("%d\n", ans);
	return 0;
}
