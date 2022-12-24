#include <stdio.h>
typedef long long LL;
int bits[1 << 16 | 1];
inline int calc(unsigned x) {
	return bits[x >> 16] + bits[x & 65535];
}
inline int calc(LL x, LL len) {
	if(len < 63)
		x &= (1ULL << len) - 1;
	return calc((unsigned)x) + calc((unsigned)(x >> 32));
}
int main() {
	for(int i = 1; i < 1 << 16; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	int t;
	scanf("%d", &t);
	while(t--) {
		LL X, L, N;
		scanf("%lld%lld%lld", &X, &L, &N);
		N <<= 1;
		L = L / N + 1;
		printf("%lld\n", (N * L) | (calc(--X, L + 1) & 1));
	}
	return 0;
}
