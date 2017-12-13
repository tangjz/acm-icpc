#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL solve(LL sta, LL end, LL stp) {
	LL ret = 0, len = (end - sta) / stp + 1;
	end -= (end - sta) % stp;
	for(LL i = 1; i <= end; i <<= 1) {
		LL a = stp, b = sta, c = i, n = len, ctr = 0;
		while(n) {
			LL u = a / c, v = b / c;
			ctr ^= (((n & 3) >= 2 ? u : 0) + ((n & 1) ? v : 0)) & 1;
			a -= u * c;
			n = a * n + b - v * c;
			b = n % c;
			n /= c;
			swap(a, c);
		}
		if(ctr)
			ret |= i;
	}
	return ret;
}
int main() {
	for(LL x, y, z; scanf("%lld%lld%lld", &x, &y, &z) == 3; printf("%lld\n", solve(x, y, z)));
	return 0;
}
