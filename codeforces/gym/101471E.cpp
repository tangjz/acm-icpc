#include <cstdio>
typedef long double DB;
const int maxn = 1001, maxt = 101;
const DB eps = 1e-12;
int n, m, a[maxn], b[maxn];
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
inline bool check(DB c) {
	DB sum = 0;
	for(int i = 0; i < n; ++i) {
		if(sgn(b[i] + c) <= 0)
			return 0;
		sum += a[i] / (b[i] + c);
	}
	return sgn(sum - m) <= 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", a + i, b + i);
	DB L = -1e3, R = 1e7, M;
	for(int i = 0; i < maxt; ++i) {
		M = R - (R - L) * 0.5;
		if(check(M))
			R = M;
		else
			L = M;
	}
	printf("%.20f\n", (double)R);
	return 0;
}
