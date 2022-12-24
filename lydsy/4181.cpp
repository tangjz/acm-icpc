#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
const int maxn = 17;
const DB eps = 1 / (DB)1e15;
int n;
DB mat[maxn][maxn], poly[maxn][maxn], rt[maxn][2];
inline DB eval(int deg, DB poly[], DB x) {
	DB ret = 0;
	for(int i = deg; i >= 0; --i)
		ret = ret * x + poly[i];
	return ret;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			double x;
			scanf("%lf", &x);
			mat[i][j] = i == j ? x : x / 2;
		}
	for(int i = 0; i + 1 < n; ++i) {
		int k = i + 1;
		for(int j = i + 2; j < n; ++j)
			if(fabs(mat[j][i]) > fabs(mat[k][i]))
				k = j;
		if(k != i + 1) {
			for(int j = i; j < n; ++j)
				swap(mat[i + 1][j], mat[k][j]);
			for(int j = 0; j < n; ++j)
				swap(mat[j][k], mat[j][i + 1]);
		}
		if(fabs(mat[i + 1][i]) < eps)
			continue;
		for(int j = i + 2; j < n; ++j) {
			DB prd = mat[j][i] / mat[i + 1][i];
			for(int k = i; k < n; ++k)
				mat[j][k] -= prd * mat[i + 1][k];
			for(int k = 0; k < n; ++k)
				mat[k][i + 1] += prd * mat[k][j];
		}
	}
	poly[n][0] = 1;
	for(int i = n - 1; i >= 0; --i) {
		poly[i][0] = 0;
		memcpy(poly[i] + 1, poly[i + 1], (n - i) * sizeof(DB));
		for(int j = 0; j < n - i; ++j)
			poly[i][j] -= mat[i][i] * poly[i + 1][j];
		DB prd = 1;
		for(int j = i + 1; j < n; ++j) {
			prd *= mat[j][j - 1];
			DB coeff = prd * mat[i][j];
			for(int k = 0; k < n - j; ++k)
				poly[i][k] -= coeff * poly[j + 1][k];
		}
	}
	for(int i = 1; i < n; ++i)
		for(int j = 0; j <= n - i; ++j)
			poly[i][j] = poly[i - 1][j + 1] * (j + 1) / (n - i + 1);
	rt[n - 1][0] = rt[n - 1][1] = -poly[n - 1][0];
	for(int i = n - 2; i >= 0; --i) {
		DB &rtL = rt[i][0] = rt[i + 1][0] - 1;
		while(1) {
			DB num = eval(n - i, poly[i], rtL);
			if(fabs(num) < eps)
				break;
			rtL -= num / (n - i) / eval(n - i - 1, poly[i + 1], rtL);
		}
		DB &rtR = rt[i][1] = rt[i + 1][1] + 1;
		while(1) {
			DB num = eval(n - i, poly[i], rtR);
			if(fabs(num) < eps)
				break;
			rtR -= num / (n - i) / eval(n - i - 1, poly[i + 1], rtR);
		}
	}
	double ans = 1 / sqrtl(max(fabs(rt[0][0]), fabs(rt[0][1])));
	printf("%.10f\n", ans);
	return 0;
}