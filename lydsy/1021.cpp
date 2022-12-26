#include <bits/stdc++.h>
using namespace std;
const int maxt = 6, w[maxt + 1] = {1, 5, 10, 20, 50, 100, 1000}, com[maxt + 1] = {1, 5, 10, 10, 50, 100, 1000};
const int maxv = 201, INF = 0x3f3f3f3f;
int tot, p, q, c[5][maxt + 1], f[2][maxv][maxv], cur, pre = 1;
void init() {
	int sum[3] = {}, dif[3];
	scanf("%d%d%d", dif + 0, dif + 1, dif + 2);
	for(int i = 0; i < 3; ++i)
		for(int j = maxt - 1; j >= 0; --j) {
			scanf("%d", c[i] + j);
			c[3][j] += c[i][j];
			int adt = c[i][j] * w[j];
			tot += adt;
			sum[i] += adt;
		}
	p = sum[0] - dif[0] + dif[2];
	q = sum[1] - dif[1] + dif[0];
	if(p < 0 || q < 0) {
		puts("impossible");
		exit(0);
	}
	int rate = com[1] / com[0], pr = p % rate, qr = q % rate, ntot = (tot - pr - qr) / rate;
	for(int i = 0; i <= ntot; ++i)
		memset(f[cur][i], 0x3f, (ntot - i + 1) * sizeof(int));
	for(int i = 0; i <= c[3][0]; ++i)
		for(int j = 0; i + j <= c[3][0]; ++j) {
			int x = sum[0] + i - c[0][0];
			int y = sum[1] + j - c[1][0];
			if(x >= 0 && y >= 0 && x + y <= tot && x % rate == pr && y % rate == qr)
				f[cur][x / rate][y / rate] = (abs(i - c[0][0]) + abs(j - c[1][0]) + abs(c[3][0] - i - j - c[2][0])) / 2;
		}
	tot = ntot;
	p /= rate;
	q /= rate;
}
void solve() {
	for(int i = 1; i < maxt; ++i) {
		int rate = com[i + 1] / com[i], pr = p % rate, qr = q % rate, ntot = (tot - pr - qr) / rate;
		swap(cur, pre);
		for(int j = 0; j <= ntot; ++j)
			memset(f[cur][j], 0x3f, (ntot - j + 1) * sizeof(int));
		int ww = w[i] / com[i], upp = c[3][i], p0 = c[0][i], p1 = c[1][i], p2 = c[2][i];
		for(int j = 0; j <= tot; ++j)
			for(int k = 0; j + k <= tot; ++k) {
				int src = f[pre][j][k];
				if(src == INF)
					continue;
				for(int x = 0; x <= upp; ++x) {
					int jj = j + (x - p0) * ww;
					if(jj < 0 || jj % rate != pr)
						continue;
					for(int y = 0; x + y <= upp; ++y) {
						int kk = k + (y - p1) * ww;
						if(kk < 0 || jj + kk > tot || kk % rate != qr)
							continue;
						int &dst = f[cur][jj / rate][kk / rate];
						dst = min(dst, src + ((abs(x - p0) + abs(y - p1) + abs(upp - x - y - p2)) / 2));
					}
				}
			}
		tot = ntot;
		p /= rate;
		q /= rate;
	}
	if(f[cur][p][q] == INF) {
		puts("impossible");
	} else {
		printf("%d\n", f[cur][p][q]);
	}
}
int main() {
	init();
	solve();
	return 0;
}
