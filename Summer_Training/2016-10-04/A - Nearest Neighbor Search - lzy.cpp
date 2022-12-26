#include <cstdio>
#include <algorithm>

using std::min;

const int inf = 0x7fffffff;

int x0, y0, z0;
int x1, y1, z1;
int x2, y2, z2;

int ans = inf;

bool x, y, z;

int sqr(int x) {
	return x * x;
}

int main() {
	scanf("%d%d%d", &x0, &y0, &z0);
	scanf("%d%d%d", &x1, &y1, &z1);
	scanf("%d%d%d", &x2, &y2, &z2);
	x = x1 <= x0 && x0 <= x2;
	y = y1 <= y0 && y0 <= y2;
	z = z1 <= z0 && z0 <= z2;
	if (x && y && z) {
		puts("0");
		return 0;
	}
	if (x && y) {
		ans = min(sqr(z0 - z1), sqr(z0 - z2));
		printf("%d\n", ans);
		return 0;
	}
	if (x && z) {
		ans = min(sqr(y0 - y1), sqr(y0 - y2));
		printf("%d\n", ans);
		return 0;
	}
	if (y && z) {
		ans = min(sqr(x0 - x1), sqr(x0 - x2));
		printf("%d\n", ans);
		return 0;
	}
	if (x) {
		ans = min(ans, sqr(y0 - y1) + sqr(z0 - z1));
		ans = min(ans, sqr(y0 - y1) + sqr(z0 - z2));
		ans = min(ans, sqr(y0 - y2) + sqr(z0 - z1));
		ans = min(ans, sqr(y0 - y2) + sqr(z0 - z2));
		printf("%d\n", ans);
		return 0;
	}
	if (y) {
		ans = min(ans, sqr(x0 - x1) + sqr(z0 - z1));
		ans = min(ans, sqr(x0 - x1) + sqr(z0 - z2));
		ans = min(ans, sqr(x0 - x2) + sqr(z0 - z1));
		ans = min(ans, sqr(x0 - x2) + sqr(z0 - z2));
		printf("%d\n", ans);
		return 0;
	}
	if (z) {
		ans = min(ans, sqr(y0 - y1) + sqr(x0 - x1));
		ans = min(ans, sqr(y0 - y1) + sqr(x0 - x2));
		ans = min(ans, sqr(y0 - y2) + sqr(x0 - x1));
		ans = min(ans, sqr(y0 - y2) + sqr(x0 - x2));
		printf("%d\n", ans);
		return 0;
	}
	if (!x && !y && !z) {
		ans = min(ans, sqr(x0 - x1) + sqr(y0 - y1) + sqr(z0 - z1));
		ans = min(ans, sqr(x0 - x1) + sqr(y0 - y1) + sqr(z0 - z2));
		ans = min(ans, sqr(x0 - x1) + sqr(y0 - y2) + sqr(z0 - z1));
		ans = min(ans, sqr(x0 - x1) + sqr(y0 - y2) + sqr(z0 - z2));
		ans = min(ans, sqr(x0 - x2) + sqr(y0 - y1) + sqr(z0 - z1));
		ans = min(ans, sqr(x0 - x2) + sqr(y0 - y1) + sqr(z0 - z2));
		ans = min(ans, sqr(x0 - x2) + sqr(y0 - y2) + sqr(z0 - z1));
		ans = min(ans, sqr(x0 - x2) + sqr(y0 - y2) + sqr(z0 - z2));
		printf("%d\n", ans);
		return 0;
	}
	return 0;
}
