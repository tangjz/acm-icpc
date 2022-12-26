#include <bits/stdc++.h>
using namespace std;
const int maxn = 41, maxm = 68921;
int tt, Case, n, tr[3][3], s[3], t[3], dis[maxm], que[maxm], L, R;
char pre[maxm], buf[maxm];
inline int idx(int x, int y, int z) {
	return (x * maxn + y) * maxn + z;
}
inline void rdx(int o, int &x, int &y, int &z) {
	z = o % maxn;
	o /= maxn;
	y = o % maxn;
	x = o / maxn;
}
int main() {
	scanf("%d", &tt);
	while(tt--) {
		scanf("%d%d", &Case, &n);
		for(int i = 0; i < 3; ++i)
			scanf("%d%d%d", tr[i] + 0, tr[i] + 1, tr[i] + 2);
		printf("%d %d\n", Case, n);
		while(n--) {
			scanf("%d%d%d%d%d%d%d", &Case, s + 0, s + 1, s + 2, t + 0, t + 1, t + 2);
			memset(dis, -1, sizeof dis);
			int S = idx(s[0], s[1], s[2]), T = idx(t[0], t[1], t[2]);
			L = R = 0;
			dis[S] = 0;
			que[R++] = S;
			while(L < R && dis[T] == -1) {
				int udx = que[L++], u[3];
				rdx(udx, u[0], u[1], u[2]);
				for(int i = 0; i < 3; ++i) {
					if(u[i]) { // forward
						int v[3] = {u[0] + tr[i][0], u[1] + tr[i][1], u[2] + tr[i][2]};
						--v[i];
						if(v[0] < maxn && v[1] < maxn && v[2] < maxn) {
							int vdx = idx(v[0], v[1], v[2]);
							if(dis[vdx] == -1) {
								que[R++] = vdx;
								pre[vdx] = 'A' + i;
								dis[vdx] = dis[udx] + 1;
							}
						}
					}
					if(u[0] >= tr[i][0] && u[1] >= tr[i][1] && u[2] >= tr[i][2]) { // backward
						int v[3] = {u[0] - tr[i][0], u[1] - tr[i][1], u[2] - tr[i][2]};
						++v[i];
						if(v[0] < maxn && v[1] < maxn && v[2] < maxn) {
							int vdx = idx(v[0], v[1], v[2]);
							if(dis[vdx] == -1) {
								que[R++] = vdx;
								pre[vdx] = 'a' + i;
								dis[vdx] = dis[udx] + 1;
							}
						}
					}
				}
			}
			if(dis[T] == -1)
				printf("%d NO SOLUTION\n", Case);
			else {
				for(int i = dis[T], cur = T; i--; ) {
					int seq[3];
					rdx(cur, seq[0], seq[1], seq[2]);
					buf[i] = pre[cur];
					if(pre[cur] >= 'A' && pre[cur] <= 'C') {
						int op = pre[cur] - 'A';
						for(int j = 0; j < 3; ++j)
							seq[j] -= tr[op][j];
						++seq[op];
					} else {
						int op = pre[cur] - 'a';
						for(int j = 0; j < 3; ++j)
							seq[j] += tr[op][j];
						--seq[op];
					}
					cur = idx(seq[0], seq[1], seq[2]);
				}
				buf[dis[T]] = '\0';
				printf("%d %d %s\n", Case, dis[T], buf);
				/*
				for(int i = 0; i < dis[T]; ++i) {
					if(buf[i] >= 'A' && buf[i] <= 'C') {
						int op = buf[i] - 'A';
						assert(s[op] > 0);
						--s[op];
						for(int j = 0; j < 3; ++j)
							s[j] += tr[op][j];
					} else {
						int op = buf[i] - 'a';
						for(int j = 0; j < 3; ++j) {
							s[j] -= tr[op][j];
							assert(s[j] >= 0);
						}
						++s[op];
					}
				}
				for(int i = 0; i < 3; ++i)
					assert(s[i] == t[i]);
				*/
			}
		}
	}
	return 0;
}
