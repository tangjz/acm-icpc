#include <cstdio>
#include <cstring>

#define N 100000

typedef long long i64;

int n, a[N + 9];
int c[11][7];
i64 ans;

int calc(int x) {
	i64 n = 1;
	int m = 0;
	while (n <= x) n *= 10, ++m;
	//printf("%d %d %d\n", m, (7 - x % 7) % 7, c[m][(7 - x % 7) % 7]);
	return c[m][(7 - x % 7) % 7];
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	memset(c, 0, sizeof c);
	for (int i = 0; i < n; ++i) {
		ans += calc(a[i]);
		
		//printf("%lld\n", ans);
		++c[0][a[i] % 7];
		i64 d = 1;
		for (int j = 1; j <= 10; ++j) {
			d = d * 10 % 7;
			++c[j][a[i] * d % 7];
		}
		
	}
	memset(c, 0, sizeof c);
	for (int i = n - 1; i >= 0; --i) {
		ans += calc(a[i]);
		//printf("%lld\n", ans);
		++c[0][a[i] % 7];
		i64 d = 1;
		for (int j = 1; j <= 10; ++j) {
			d = d * 10 % 7;
			++c[j][a[i] * d % 7];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
