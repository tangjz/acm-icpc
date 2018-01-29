#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, FZ = 15499, FM = 94744;
int phi[maxn];
int main() {
	int fz = 1, fm = 1;
	for(int i = 1; i < maxn; ++i) {
		phi[i] += i;
		for(int j = i + i; j < maxn; j += i)
			phi[j] -= phi[i];
		if((LL)phi[i] * fm < (i - 1LL) * fz)
			printf("%d: %d/%d\n", i, fz = phi[i], fm = i - 1);
	}
	LL ans = 2;
	while(1) {
		LL tmp = ans, phi = ans, rad = 1;
		for(int i = 2; (LL)i * i <= tmp; ++i)
			if(tmp % i == 0) {
				for( ; tmp % i == 0; tmp /= i);
				phi -= phi / i;
				rad *= i;
			}
		if(tmp > 1) {
			phi -= phi / tmp;
			rad *= tmp;
		}
		printf("%lld: %.10f\n", ans, phi / (ans - 1.0));
		if(phi * FM < (ans - 1) * FZ)
			break;
		ans += rad;
	}
	return 0;
}
