#include <cstdio>
#include <algorithm>

using namespace std;

#define N 1000009

int n, m, x, y, s, t, a, b, p, q;
int c[2 * N], d[2 * N], e[2 * N], f[2 * N];
long long ans;

int main() {
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d", &x, &y);
		c[a++] = x + y;
		d[b++] = x - y;
	}
	sort(c, c + a);
	a=unique(c, c + a) - c;
	sort(d, d + b);
	b=unique(d, d + b) - d;
	for (int i = 0; i < a; ++i) {
		int k = c[i];
		ans += min(k - 1, n) - max(k - n, 1) + 1;
	}
	for (int i = 0; i < b; ++i) {
		int k = d[i];
		ans += min(n + k, n) - max(1 + k, 1) + 1;
		if (k & 1) e[p++] = k;
		else f[q++] = k;
	}
	while (a--) {
		int k = c[a];
		if (k <= n + 1) {
			s = 2 - k;
			t = k - 2;
		} else {
			s = k - 2 * n;
			t = 2 * n - k;
		}
		int *l, *r;
		if (k & 1) {
			l = lower_bound(e, e + p, s);
			r = upper_bound(e, e + p, t);
		}
		else {
			l = lower_bound(f, f + q, s);
			r = upper_bound(f, f + q, t);
		}
		ans -= r - l;
	}
	printf("%lld\n", (long long)n * n - ans);
	return 0;
}

