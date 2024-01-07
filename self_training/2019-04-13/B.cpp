#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxd = 18, maxn = 7, mod[maxn] = {16, 9, 5, 7, 11, 13, 17};
int t, n, m, coeff[maxn];
inline int mod_inv(int x, int m) {
	int y = m, u = 1, v = 0;
	while(x) {
		int q = y / x;
		swap(x, y);
		x -= q * y;
		swap(u, v);
		u -= q * v;
	}
	return v < 0 ? v + m : v;
}
int main() {
	int MOD = 1;
	for(int i = 0; i < maxn; ++i)
		MOD *= mod[i];
	for(int i = 0; i < maxn; ++i) {
		int tmp = MOD / mod[i];
		coeff[i] = (LL)mod_inv(tmp % mod[i], mod[i]) * tmp % MOD;
	}
	scanf("%d%d%d", &t, &n, &m);
	for(int Case = 1; Case <= t; ++Case) {
		int ans = 0;
		for(int i = 0; i < maxn; ++i) {
			for(int j = 0; j < maxd; ++j)
				printf("%d%c", mod[i], " \n"[j == maxd - 1]);
			fflush(stdout);
			int adt = 0;
			for(int j = 0; j < maxd; ++j) {
				int ret = -1;
				scanf("%d", &ret);
				if(ret == -1) {
					// fprintf(stderr, "crushed [ret = %d]\n", ret);
					exit(0);
				}
				adt += ret;
			}
			ans = (ans + (LL)coeff[i] * adt) % MOD;
		}
		printf("%d\n", ans);
		fflush(stdout);
		int ret = -1;
		scanf("%d", &ret);
		if(ret != 1) {
			// fprintf(stderr, "crushed [ret = %d]\n", ret);
			exit(0);
		}
	}
	return 0;
}