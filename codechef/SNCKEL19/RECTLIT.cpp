#include <bits/stdc++.h>
using namespace std;
const int maxn = 11;
int t, n, m, x[maxn], y[maxn], qx[maxn], qy[maxn], c[maxn][maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &m, &n);
		if(m > 4) {
			puts("yes");
			while(m--)
				scanf("%*d%*d");
			continue;
		}
		qx[0] = qy[0] = 0;
		qx[++qx[0]] = qy[++qy[0]] = 0;
		qx[++qx[0]] = qy[++qy[0]] = n;
		for(int i = 0; i < m; ++i) {
			scanf("%d%d", x + i, y + i);
			qx[++qx[0]] = x[i];
			qx[++qx[0]] = x[i] + 1;
			qy[++qy[0]] = y[i];
			qy[++qy[0]] = y[i] + 1;
		}
		sort(qx + 1, qx + qx[0] + 1);
		qx[0] = unique(qx + 1, qx + qx[0] + 1) - qx - 2;
		sort(qy + 1, qy + qy[0] + 1);
		qy[0] = unique(qy + 1, qy + qy[0] + 1) - qy - 2;
		for(int i = 0; i < m; ++i) {
			x[i] = lower_bound(qx + 1, qx + qx[0] + 1, x[i]) - qx - 1;
			y[i] = lower_bound(qy + 1, qy + qy[0] + 1, y[i]) - qy - 1;
		}
		bool chk = 0;
		for(int i = 0; !chk && i < 1 << (m + m); ++i) {
			for(int j = 0; j < qx[0]; ++j)
				memset(c[j], 0, qy[0] * sizeof(int));
			for(int j = 0, tmp = i; j < m; ++j, tmp >>= 2) {
				int xL = tmp & 1 ? x[j] : 0;
				int xR = tmp & 1 ? qx[0] : x[j] + 1;
				int yL = tmp & 2 ? y[j] : 0;
				int yR = tmp & 2 ? qy[0] : y[j] + 1;
				++c[xL][yL];
				--c[xL][yR];
				--c[xR][yL];
				++c[xR][yR];
			}
			for(int j = 1; j < qx[0]; ++j)
				for(int k = 0; k < qy[0]; ++k)
					c[j][k] += c[j - 1][k];
			chk = 1;
			for(int j = 0; chk && j < qx[0]; ++j) {
				chk &= c[j][0] > 0;
				for(int k = 1; chk && k < qy[0]; ++k) {
					c[j][k] += c[j][k - 1];
					chk &= c[j][k] > 0;
				}
			}
		}
		puts(chk ? "yes" : "no");
	}
	return 0;
}
