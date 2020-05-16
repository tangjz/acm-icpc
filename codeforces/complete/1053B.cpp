#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1, maxd = 1 << 16 | 1;
int n, a[maxn], b[2][maxn], bits[maxd];
LL ans;
inline int calc(unsigned x) {
	return bits[x & ((1 << 16) - 1)] + bits[x >> 16];
}
inline int calc(LL x) {
	return calc((unsigned)x) + calc((unsigned)(x >> 32));
}
int main() {
	for(int i = 1; i < maxd; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	scanf("%d", &n);
	for(int i = 1, o = 0; i <= n; ++i) {
		LL x;
		scanf("%lld", &x);
		a[i] = calc(x);
		b[0][i] = b[0][i - 1];
		b[1][i] = b[1][i - 1];
		++b[o][i];
		o = (o + a[i]) & 1;
		int mx = 0, sum = 0;
		for(int j = i; j >= 1; --j) {
			if(sum >= 128) {
				ans += b[o][j];
				break;
			}
			mx = max(mx, a[j]);
			sum += a[j];
			if(mx + mx <= sum && !(sum & 1)) {
				++ans;
//				printf("%d %d ok: %d %d\n", j, i, mx, sum);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}