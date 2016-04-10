#include <cstdio>
#include <algorithm>
 
using namespace std;
 
#define N 100000
 
const double eps = 1e-7;
 
int T, n, P, k, m;
int a, s[N + 9], t[N + 9], x[N + 9];
double c[N + 9], d[N + 9], f[N + 9];
 
int dcmp(double x) {
	return (x>+eps) - (x<-eps);
}
 
void upc(int k, double v) {
	for (int i = ++k; i <= m; i += i & -i) c[i] = min(c[i], v);
}
 
void upd(int k, double v) {
	for (int i = ++k; i >= 1; i -= i & -i) d[i] = min(d[i], v);
}
 
double getc(int k) {
	double ret = 1e12;
	for (int i = ++k; i >= 1; i -= i & -i) ret = min(ret, c[i]);
	return ret;
}
 
double getd(int k) {
	double ret = 1e12;
	for (int i = ++k; i <= m; i += i & -i) ret = min(ret, d[i]);
	return ret;
}
 
int check(double mid) {
	for (int i = 1; i <= m; ++i) {
		c[i] = d[i] = 1e12;
	}
	for (int i = 0; i <= n; ++i) {
		f[i] = s[i] - i * mid;
		if (i >= k) {
			upc(t[i - k], f[i - k]);
			upd(t[i - k], f[i - k]);
 
		//printf("i : %d\n", i);
 
			double y;
			y = getc(t[i]);
			if (dcmp(f[i] - y) >= 0) return i;
			y = getd(t[i] + 1);
			if (dcmp(f[i] + P - y) >= 0) return i;
		}
	}
	return -1;
}
 
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &P, &k);
		s[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a);
			s[i] = (s[i - 1] + a) % P;
			x[i] = s[i];
		}
		sort(x, x + n + 1);
		m = unique(x, x + n + 1) - x;
		for (int i = 0; i <= n; ++i) t[i] = lower_bound(x, x + m, s[i]) - x;
 
		double l = 0, r = 1e10, mid;
		for (int cnt = 0; cnt < 60; ++cnt) {
			mid = (l + r) / 2;
			if (check(mid) == -1) r = mid;
			else l = mid;
		}
 
		int p = check(l - eps), q;
		if (p < k) {
			puts("0 1");
			continue;
		}
		//printf("%f %d",l, p);
		double ans = 0;
		for (int i = 0; i + k <= p; ++i) {
			if (ans < (double)((s[p] - s[i] + P) % P)/(p - i)) {
				q = i;
				ans = (double)((s[p] - s[i] + P) % P)/(p - i);
			}
		}
		if (q < 0 || q >= p) {
			puts("0 1");
			continue;
		}
		int a, b, g;
		a = (s[p] - s[q] + P) % P;
		b = p - q;
		g =__gcd(a, b);
		printf("%d %d\n", a / g, b / g);
	}
	return 0;
}
