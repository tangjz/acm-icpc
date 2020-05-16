#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, maxm = maxn * maxn;
const int dx[6] = {-1, -1, 0, 1, 0, -1}, dy[6] = {0, 1, 1, 0, -1, -1};
const int sx[6] = {-2, -1, 1, 2, 1, -1}, sy[6] = {0, 3, 3, 0, -3, -3};
int t, n, m, S, T, e[maxm][6], que[maxm], dis[maxm];
char buf[maxn * 4 | 1][maxn * 6 | 1];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%*[^\n]", &n, &m);
		getchar();
		for(int i = 0; i < n * 4 + 3; ++i) {
			scanf("%[^\n]", buf[i]);
			getchar();
		}
		for(int i = 0, idx = 0; i < n; ++i)
			for(int j = 0; j < m; ++j, ++idx) {
				int x = i * 4 + 2, y = j * 6 + 4;
				if(j & 1)
					x += 2;
				if(buf[x][y] == 'S')
					S = idx;
				if(buf[x][y] == 'T')
					T = idx;
				for(int d = 0; d < 6; ++d) {
					int xx = x + sx[d], yy = y + sy[d];
					e[idx][d] = buf[xx][yy] == ' ';
				}
			}
		memset(dis, -1, n * m * sizeof(int));
		dis[S] = 1;
		que[0] = S;
		for(int i = 0, tot = 1; i < tot && dis[T] == -1; ++i) {
			int udx = que[i], ux = udx / m, uy = udx % m;
			for(int d = 0; d < 6; ++d) {
				if(!e[udx][d])
					continue;
				int vx = ux + dx[d], vy = uy + dy[d];
				if(uy & 1 && dy[d])
					++vx;
				int vdx = vx * m + vy;
				if(dis[vdx] == -1) {
					dis[vdx] = dis[udx] + 1;
					que[tot++] = vdx;
				}
			}
		}
		printf("%d\n", dis[T]);
	}
	return 0;
}
