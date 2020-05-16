#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
	LL k, d, t;
	scanf("%lld%lld%lld", &k, &d, &t);
	LL x = (k - 1) / d + 1;
	LL y = x * d + k;
	LL z = 2 * t / y;
	LL u = 2 * t - y * z;
	LL v = 2 * x * d * z + max(u, (u - k) << 1);
	printf("%lld.%c\n", v >> 1, "05"[v & 1]);
	return 0;
}
