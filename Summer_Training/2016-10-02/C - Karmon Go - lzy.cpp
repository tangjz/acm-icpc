#include <cstdio>

typedef long long i64;

int k0, k1;
double cc;
i64 a, b;

int main() {
	scanf("%*s%d%*s%lf%d", &k0, &cc, &k1);
	a = k0 * (i64)(cc * 100000 + .5);
	b = k1 * 100000LL;
	if (a == b) puts("Whatever");
	else if (a < b) puts("Evolve, Power up");
	else puts("Power up, Evolve");
	return 0;
}
