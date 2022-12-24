#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxs = 85;
int t, mx, pos, cnt;
LL fib[maxs], x;
int main() {
	fib[0] = 1;
	fib[1] = 2;
	mx = 1;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld", &x);
		for( ; fib[mx] <= x; ++mx)
			fib[mx + 1] = fib[mx] + fib[mx - 1];
		for(pos = 0; fib[pos + 1] <= x; ++pos);
		for(cnt = 0; x > 0; ++cnt) {
			for( ; fib[pos] > x; --pos);
			x = min(x - fib[pos], fib[pos + 1] - x);
		}
		printf("%d\n", cnt);
	}
	return 0;
}