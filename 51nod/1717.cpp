#include <cmath>
#include <cstdio>
long long n, m;
int main() {
	scanf("%lld", &n);
	m = (long long)ceil(sqrt(n));
	for( ; m * m <= n; ++m);
	for( ; m * m > n; --m);
	printf("%lld\n", n - m);
	return 0;
}
