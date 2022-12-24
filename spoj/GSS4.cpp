#include <cmath>
#include <cstdio>
typedef long long LL;
const int maxn = 100001;
int n, m, dsu[maxn];
LL a[maxn], bit[maxn];
inline int dsu_find(int x) {
	return dsu[x] < 0 ? x : dsu[x] = dsu_find(dsu[x]);
}
inline void bit_add(int x, LL v) {
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
inline LL bit_sum(int x) {
	LL ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main() {
	dsu[0] = -1;
	for(int Case = 1; scanf("%d", &n) == 1; ++Case) {
		for(int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			dsu[i] = a[i] > 1 ? -1 : dsu_find(i - 1);
			bit[i] = a[i];
		}
		for(int i = 1, j; i <= n; ++i)
			if((j = i + (i & -i)) <= n)
				bit[j] += bit[i];
		scanf("%d", &m);
		printf("Case #%d:\n", Case);
		while(m--) {
			int typ, L, R;
			scanf("%d%d%d", &typ, &L, &R);
			if(L > R) {
				L = L + R;
				R = L - R;
				L = L - R;
			}
			if(!typ) { // modify
				for(int i = dsu_find(R); i >= L; i = dsu_find(i - 1)) {
					LL val = (LL)sqrt(a[i]);
					bit_add(i, val - a[i]);
					a[i] = val;
					dsu[i] = a[i] > 1 ? -1 : dsu_find(i - 1);
				}
			} else { // query
				printf("%lld\n", bit_sum(R) - bit_sum(L - 1));
			}
		}
		puts("");
	}
	return 0;
}