#include <bits/stdc++.h>
typedef double DB;
const int maxd = 10, maxs = 101, maxl = 6;
int m, e, sz;
DB lpw[maxd + 1][maxs], c[maxs][maxs];
DB f[maxs], mat[maxs][maxs << 1 | 1], ans;
void dfs(int dep, int val, int msk) {
	if(dep == maxl) {
		DB prd = 1;
		for(int i = 0; i < e; ++i)
			f[i * m + msk] += 1 / (prd *= val);
		return;
	}
	ans += 1.0 / val;
	for(int i = 0; i < maxd; ++i) {
		if(msk & 1 && (msk >> 1) == i)
			continue;
		dfs(dep + 1, val * maxd + i, i << 1 | ((msk >> 1) == i));
	}
}
int main() {
	m = maxd << 1;
	e = (maxs - 1) / m;
	sz = e * m;
	lpw[0][0] = 0;
	for(int i = 1; i <= maxd; ++i) {
		lpw[i][0] = 0;
		lpw[i][1] = log(i);
		for(int j = 2; j < e; ++j)
			lpw[i][j] = lpw[i][j - 1] + lpw[i][1];
	}
	lpw[maxd][e] = lpw[maxd][e - 1] + lpw[maxd][1];
	for(int i = 0; i < e; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	for(int i = 0; i < sz; ++i)
		mat[i][i] = mat[i][sz + i] = 1;
	for(int i = 0; i < m; ++i)
		for(int d = 0; d < maxd; ++d) {
			if(i & 1 && (i >> 1) == d)
				continue;
			int ii = d << 1 | ((i >> 1) == d);
			for(int j = 0; j < e; ++j)
				for(int jj = 0; jj <= j; ++jj) {
					if(!d && jj < j)
						continue;
					mat[j * m + i][jj * m + ii] -= ((j - jj) & 1 ? -1 : 1) * exp(log(c[j][jj]) + lpw[d][j - jj] - lpw[maxd][j + 1]);
				}
		}
	for(int i = 0, j, k; i < sz; ++i) {
		for(j = i, k = j + 1; k < sz; ++k)
			if(fabs(mat[k][i]) > fabs(mat[j][i]))
				j = k;
//		assert(fabs(mat[j][i]) > 1e-20);
		DB prd = mat[j][i];
		for(k = i; k < sz << 1; ++k) {
			std::swap(mat[j][k], mat[i][k]);
			mat[i][k] /= prd;
		}
		for(j = 0; j < sz; ++j) {
			if(i == j)
				continue;
			DB prd = mat[j][i];
			for(int k = i; k < sz << 1; ++k)
				mat[j][k] -= prd * mat[i][k];
		}
	}
	for(int i = 1; i < maxd; ++i)
		dfs(1, i, i << 1);
	for(int i = 0; i < sz; ++i)
		for(int j = 0; j < m; ++j)
			ans += f[i] * mat[i][sz + j];
	printf("%.10f\n", (double)ans);
	return 0;
}
