#include <cstdio>

int n, a, s, b;

int main() {
	scanf("%d", &n);
	b = 1009;
	while (n--) {
		scanf("%d", &a);
		s += a;
		if (a & 1 && b > a) b = a;
	}
	if (s & 1) s -= b;
	if (s) printf("%d\n", s);
	else puts("NIESTETY");
	return 0;
}
