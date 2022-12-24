#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 101;
const DB eps = 1e-12;
int t, n, m;
DB p[maxn][maxn], mat[maxn][maxn], cen[maxn];
bool vis[maxn];
int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		memset(vis, 0, n * sizeof(bool));
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				double x;
				scanf("%lf", &x);
				p[i][j] = x;
				mat[i][j] = p[i][j] - p[0][j];
			}
			for(int j = 1; j <= i; ++j) {
				DB prd = 0;
				for(int k = 0; k < n; ++k)
					prd += mat[i][k] * mat[j][k];
				if(j < i) {
					for(int k = 0; k < n; ++k)
						mat[i][k] -= prd * mat[j][k];
				} else {
					prd = sqrtl(prd);
					for(int k = 0; k < n; ++k)
						mat[i][k] /= prd;
				}
			}
		}
		for(int i = m, mx = 0; i <= n; ++i) {
			while(1) {
				bool chk = 0;
				assert(mx < n);
				for(int j = 0; j < n; ++j)
					mat[i][j] = j == mx;
				for(int j = 1; j <= i; ++j) {
					DB prd = 0;
					for(int k = 0; k < n; ++k)
						prd += mat[i][k] * mat[j][k];
					if(j < i) {
						for(int k = 0; k < n; ++k)
							mat[i][k] -= prd * mat[j][k];
					} else {
						prd = sqrtl(prd);
						if(!sgn(prd))
							break;
						chk = 1;
						for(int k = 0; k < n; ++k)
							mat[i][k] /= prd;
					}
				}
				if(chk)
					break;
				++mx;
			}
			for(int j = 0; j < n; ++j)
				p[i][j] = 0;
			for(int j = 0; j < i; ++j)
				for(int k = 0; k < n; ++k)
					p[i][k] += p[j][k];
			DB prd = sqrtl((i + 1.0) / (i << 1));
			for(int j = 0; j < n; ++j)
				p[i][j] = p[i][j] / i + mat[i][j] * prd;
		}
		printf("Case #%d: %d\n", Case, n + 1 - m);
		for(int i = m; i <= n; ++i)
			for(int j = 0; j < n; ++j)
				printf("%.20f%c", (double)p[i][j], " \n"[j == n - 1]);
	}
	return 0;
}
