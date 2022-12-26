#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
const int maxn = 1 << 10 | 1, maxm = 13;
const DB eps = 1e-12;
DB a[maxm][maxn];
int n, m, t, id[maxn << 1 | 1];
void pivot(int l, int e) {
	swap(id[e], id[n + l]);
	DB r = a[l][e];
	a[l][e] = 1;
	for(int j = 0; j <= n; ++j)
		a[l][j] /= r;
	for(int i = 0; i <= m; ++i) {
		if(i == l)
			continue;
		r = a[i][e];
		a[i][e] = 0;
		for(int j = 0; j <= n; ++j)
			a[i][j] -= r * a[l][j];
	}
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int N, M, A[maxn];
		scanf("%d%d", &N, &M);
		for(int i = 0; i < N; ++i)
			scanf("%d", A + i);
		n = 1 << N;
		m = N + 1;
		for(int i = 0; i <= m; ++i)
			for(int j = 0; j <= n; ++j)
				a[i][j] = 0;
		for(int i = 0; i <= n; ++i)
			id[i] = i;
		for(int i = 0; i < n; ++i) {
			int sum = 0;
			for(int j = 0; j < N; ++j)
				if((i >> j) & 1)
					sum += A[j];
			if(sum > M)
				continue;
			if(i & 1)
				a[0][i + 1] += 1;
			for(int j = 0; j < N; ++j)
				if((i >> j) & 1) {
					a[j + 1][i + 1] += 1;
					a[j ? j : N][i + 1] -= 1;
				}
			a[m][i + 1] += 1;
		}
		a[m][0] += 1;
		while(1) {
			int l = 0, e = 0;
			DB k = -eps;
			for(int i = 1; i <= m; ++i)
				if(a[i][0] < k) {
					k = a[i][0];
					l = i;
				}
			if(!l)
				break;
			k = -eps;
			for(int j = 1; j <= n; ++j)
				if(a[l][j] < k) {
					k = a[l][j];
					e = j;
				}
			assert(e);
			pivot(l, e);
		}
		while(1) {
			int l = 0, e = n + 1;
			for(int j = 1; j <= n; ++j)
				if(a[0][j] > eps) {
					e = j;
					break;
				}
			if(e > n)
				break;
			DB k = 1e18, kk;
			for(int i = 1; i <= m; ++i)
				if(a[i][e] > eps && (kk = (a[i][0] / a[i][e])) < k) {
					k = kk;
					l = i;
				}
			assert(l);
			pivot(l, e);
		}
		printf("Case #%d: %.20f\n", Case, (double)-a[0][0]);
	}
	return 0;
}
