#include <bits/stdc++.h>
using namespace std;
const int maxn = 1001;
int t, Case, n, cur, nxt = 1;
double pL, pM, pR, f[2][maxn][maxn << 1 | 1];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%lf%lf", &Case, &n, &pL, &pR);
		pM = 1 - pL - pR;
		f[cur][0][0] = 1;
		for(int i = 0; i < n; ++i, cur ^= 1, nxt ^= 1) {
			for(int j = 0; j <= i + 1; ++j)
				memset(f[nxt][j], 0, (i - j + 2) * sizeof(double));
			for(int j = 0; j <= i; ++j)
				for(int k = 0; j + k <= i; ++k) {
					double tmp = f[cur][j][k];
					f[nxt][j][k + 1] += tmp * pL;
					f[nxt][j][k] += tmp * pM;
					(k ? f[nxt][j][k - 1] : f[nxt][j + 1][k]) += tmp * pR;
				}
		}
		double ans = 0, sum = 0;
		for(int i = n; i >= 1; --i) {
			for(int j = 0; i + j <= n; ++j)
				sum += f[cur][i][j];
			ans += sum;
		}
		printf("%d %.4f\n", Case, ans);
	}
	return 0;
}
