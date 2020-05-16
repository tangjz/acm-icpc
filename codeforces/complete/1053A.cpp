#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, m, k;
void print(int x, int y) {
	printf("YES\n0 0\n%d 0\n0 %d\n", x, y);
	exit(0);
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	if(k & 1) {
		if((2LL * n * m) % k == 0) {
			for(int i = 1; i * i <= k; ++i)
				if(k % i == 0) {
					int x = i, y = k / i;
					if((2 * n) % x == 0 && 2 * n / x <= n && m % y == 0 && m / y <= m)
						print(2 * n / x, m / y);
					if((2 * n) % y == 0 && 2 * n / y <= n && m % x == 0 && m / x <= m)
						print(2 * n / y, m / x);
					if((2 * m) % x == 0 && 2 * m / x <= m && n % y == 0 && n / y <= n)
						print(n / y, 2 * m / x);
					if((2 * m) % y == 0 && 2 * m / y <= m && n % x == 0 && n / x <= n)
						print(n / x, 2 * m / y);
				}
		}
	} else {
		k >>= 1;
		int lft = __gcd(n, k), rht = __gcd(m, k / lft);
		if((LL)lft * rht == k)
			print(n / lft, m / rht);
	}
	puts("NO");
	return 0;
}
// x * y == 2 * n * m / k