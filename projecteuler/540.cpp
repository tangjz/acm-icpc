#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)6e7 + 1;
LL f[maxn];
LL iSqrt(LL n) {
	LL ret = (LL)ceil(sqrtl(n));
	for( ; ret * ret <= n; ++ret);
	for( ; ret * ret > n; --ret);
	return ret;
}
LL calc(LL n) {
	static LL last_n = 0, ret = 0;
	if(n == last_n)
		return ret;
	last_n = n;
	ret = 0;
	for(LL i = 1, x = 1; x + (i << 2) <= n; x += i << 3, ++i) // x=(2i-1)^2
		ret += max(((iSqrt((n << 1) - x) + 1) >> 1) - i, 0LL);
	return ret;
}
int main() {
	LL n;
	while(scanf("%lld", &n) == 1) {
		for(int iLim = iSqrt(n), i = iLim - !(iLim & 1); i >= 1; i -= 2) {
			f[i] = calc(n / i / i);
			for(int j = i * 3; j <= iLim; j += i * 2)
				f[i] -= f[j];
		}
		printf("%lld\n", f[1]);
	}
	return 0;
}
