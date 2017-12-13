#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
typedef double DB;
const int maxn = 100001;
const DB eps = 1e-7, eps2 = 1e-10;
int t, n;
DB a[maxn];
bool check(DB r) {
	DB L = -r, R = r, r2 = r * r;
	for(int i = 0; i < n; ++i) {
		DB v = sqrt(r2 - a[i]);
		L = std::max(L, -v);
		R = std::min(R, v);
		if(std::abs(L) < std::abs(R))
			R -= 1;
		else
			L += 1;
		if(L > R + eps2)
			return 0;
	}
	return 1;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		DB L = 0;
		for(int i = 0; i < n; ++i) {
			double x, y;
			scanf("%lf%lf", &x, &y);
			if(x < y)
				std::swap(x, y);
			x /= 2;
			a[i] = x * x + y * y;
			L = std::max(L, sqrt(a[i]));
		}
		std::sort(a, a + n);
		DB R = L + n;
		while(R - L >= eps) {
			DB M = L + (R - L) / 2;
			if(check(M))
				R = M;
			else
				L = M;
		}
		printf("Case #%d: %.10f\n", Case, (double)L);
	}
	return 0;
}
