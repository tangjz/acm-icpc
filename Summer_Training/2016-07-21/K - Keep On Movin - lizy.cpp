#include <cstdio>

int T, n, a, x, y;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		x = y = 0;
		while (n--) {
			scanf("%d", &a);
			x += a & 1;
			y += a >> 1;
		}
		if (x == 0) {
			printf("%d\n", y * 2);
		} else {
			y -= y % x;
			printf("%d\n", y / x * 2 + 1);
		}
	}
	return 0;
}
