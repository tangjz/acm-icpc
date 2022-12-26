#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, a[maxn], fir[maxn], bit[maxn], ans[maxn];
struct Query {
	int idx, L, R;
	bool operator < (Query const &t) const {
		return R > t.R;
	}
} que[maxn];
void bit_add(int x, int v) {
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int bit_sum(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		memset(bit + 1, 0, n * sizeof(int));
		memset(fir + 1, 0, n * sizeof(int));
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if(!fir[a[i]]) {
				fir[a[i]] = i;
				bit_add(i, 1);
			}
		}
		for(int i = 1; i <= m; ++i) {
			int L, R;
			scanf("%d%d", &L, &R);
			if(L >= R)
				L = R = 1;
			que[i] = (Query){i, L, R};
		}
		sort(que + 1, que + m + 1);
		for(int i = 1, qR = n + 1; i <= m; ++i) {
			for( ; qR > que[i].R; --qR) {
				int &cur = fir[a[qR - 1]];
				if(cur > 1) {
					bit_add(cur, -1);
					cur = 1;
					bit_add(cur, 1);
				}
			}
			ans[que[i].idx] = bit_sum(que[i].L);
		}
		for(int i = 1; i <= m; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
