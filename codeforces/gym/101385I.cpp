#include <cmath>
#include <cstdio>
#include <algorithm>
const int maxn = 19, low = 0, upp = 100, maxt = 40;
const double eps = 1e-9;
int t, n, m, s, h;
double a[maxn];
int sgn(double x) {
	return (x > eps) - (x < -eps);
}
double calc() {
	double diff = 0;
	for(int i = 0; i < n; ++i)
		diff += (a[i] - m) * (a[i] - m);
	return sqrt(diff / n);
}
int main() {
	freopen("stats.in", "r", stdin);
	freopen("stats.out", "w", stdout);
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &m, &s, &h);
		if(!sgn(m - h) && !sgn(s)) {
			printf("1 %d\n", h);
			continue;
		}
		for(n = 3; n <= maxn; n += 2) {
			int md = n >> 1;
			a[md] = h;
			if(h < m) {
				double v = (n * m - (md + 1) * h) / (double)(n - md - 1);
				if(sgn(v - upp) > 0)
					continue;
				for(int i = 0; i < md; ++i)
					a[i] = h;
				for(int i = md + 1; i < n; ++i)
					a[i] = v;
			} else {
				double v = (n * m - (n - md) * h) / (double)md;
				if(sgn(v - low) < 0)
					continue;
				for(int i = 0; i < md; ++i)
					a[i] = v;
				for(int i = md + 1; i < n; ++i)
					a[i] = h;
			}
			if(sgn(calc() - s) > 0)
				continue;
			for(int i = 0, j = n - 1; i < j; ) {
				double di = i < md ? a[i] - low : a[i] - h;
				double dj = j <= md ? h - a[j] : upp - a[j];
				double dt = std::min(di, dj);
				a[i] -= dt;
				a[j] += dt;
				if(sgn(calc() - s) < 0) {
					i += !sgn(di - dt);
					j -= !sgn(dj - dt);
					continue;
				}
				a[i] += dt;
				a[j] -= dt;
				double L = 0, R = dt;
				for(int k = 0; k < maxt; ++k) {
					double M = L + (R - L) * 0.5;
					a[i] -= M;
					a[j] += M;
					if(sgn(calc() - s) < 0)
						L = M;
					else
						R = M;
					a[i] += M;
					a[j] -= M;
				}
				a[i] -= R;
				a[j] += R;
				break;
			}
			if(sgn(calc() - s) == 0)
				break;
		}
		if(n <= maxn) {
			printf("%d", n);
			for(int i = 0; i < n; ++i)
				printf(" %.20f", a[i]);
			putchar('\n');
		} else {
			puts("-1");
		}
	}
	return 0;
}
