#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
int n, eve[maxn], m, que[maxn], mx, sm, bit[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		int typ, &x = eve[i];
		scanf("%d%d", &typ, &x);
		if(typ == 1) {
			int y, z;
			scanf("%d%d", &y, &z);
			LL dis = (LL)x * x + (LL)y * y + (LL)z * z;
			x = (int)sqrtl(dis);
			for( ; x && (LL)x * x >= dis; --x);
			for( ; (LL)x * x < dis; ++x);
			//assert((LL)x * x >= dis);
			que[++m] = x;
			//assert(x >= 0);
		} else {
			x = -x - 1;
			//assert(x < 0);
		}
	}
	sort(que + 1, que + m + 1);
	m = unique(que + 1, que + m + 1) - que - 1;
	for(mx = 1; (mx << 1) <= m; mx <<= 1);
	for(int i = 1; i <= n; ++i) {
		int x = eve[i];
		if(x >= 0) {
			int k = lower_bound(que + 1, que + m + 1, x) - que;
			//assert(k <= m && que[k] == x);
			for(++sm; k <= m; k += k & -k)
				++bit[k];
		} else {
			int k = -x - 1;
			//assert(k > 0);
			if(k > sm) {
				puts("-1");
			} else if(k == 0) {
				puts("0");
			} else {
				int x = 0;
				for(int y = mx, z; y; y >>= 1)
					if((z = x | y) <= m && bit[z] < k) {
						x = z;
						k -= bit[z];
					}
				//assert(x < m);
				printf("%d\n", que[x + 1]);
			}
		}
	}
	return 0;
}