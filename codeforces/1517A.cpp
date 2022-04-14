#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL solve() {
    LL n;
    scanf("%lld", &n);
    if(n % 2050 > 0)
        return -1;
    n /= 2050;
    LL ret = 0;
    while(n > 0) {
        ret += n % 10;
        n /= 10;
    }
    return ret;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		printf("%lld\n", solve());
	}
	return 0;
}