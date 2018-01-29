#include <bits/stdc++.h>
using namespace std;
const int maxn = 13, maxs = 1 << 13 | 1;
map<int, double> f[maxs][2];
int main() {
	int n, dt, tot;
	while(scanf("%d%d%d", &n, &dt, &tot) == 3) {
		assert(n * dt < tot);
		for(int i = 0; i < 1 << n; ++i) {
			map<int, double>().swap(f[i][0]);
			map<int, double>().swap(f[i][1]);
		}
		f[0][0][0] = 1;
		int all = (1 << n) - 1;
		for(int i = 0; i <= all; ++i)
			for(int j = 0; j < 2; ++j) {
				int cnt = 0;
				static int bits[maxn + 2] = {-1};
				for(int k = 0; k < n; ++k)
					if(!(i & (1 << k)))
						bits[++cnt] = k;
				for(map<int, double>::iterator it = f[i][j].begin(); it != f[i][j].end(); ++it) {
					int dis = it -> first;
					double prb = it -> second;
					for(int k = 1; k < cnt; ++k) {
						int pre = bits[k] - bits[k - 1], nxt = bits[k + 1] - bits[k];
						int ndt = nxt * dt, ndis = dis + pre * ndt;
						f[i | 1 << bits[k]][(j + pre) & 1][ndis] += prb * ndt / ndis;
					}
					if(cnt) {
						int pre = bits[cnt] - bits[cnt - 1];
						int ndt = tot - bits[cnt] * dt, ndis = dis + pre * ndt;
						f[i | 1 << bits[cnt]][j][ndis] += prb * ndt / ndis;
					}
				}
			}
		double ans = 0;
		for(map<int, double>::iterator it = f[all][0].begin(); it != f[all][0].end(); ++it)
			ans += it -> second;
		printf("%.10f\n", ans);
	}
	return 0;
}
