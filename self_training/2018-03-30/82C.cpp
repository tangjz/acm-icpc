#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 3, maxd = 11, mod = 10;
int n, m, a[maxn], pos[maxn], bit[maxd][maxn];
struct Query {
	int idx, L, R;
	bool operator < (Query const &t) const {
		return R < t.R;
	}
} que[maxn];
char ans[maxn][maxd];
void bit_upd(int bit[], int x, int v) {
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int bit_que(int bit[], int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= m; ++i) {
		que[i].idx = i;
		scanf("%d%d", &que[i].L, &que[i].R);
	}
	sort(que + 1, que + m + 1);
	for(int i = 1, j = 1; i <= n; ++i) {
		int las = pos[a[i]], lft = 0, rht = 0, pre, cur = i;
		int ctr = 0;
		while(cur > las && (lft < maxd || rht < maxd)) {
			pre = cur;
			cur = las;
			if(lft < maxd)
				cur = max(cur, pos[max(a[i] - lft - 1, 0)]);
			if(rht < maxd)
				cur = max(cur, pos[min(a[i] + rht + 1, maxn - 1)]);
			if(lft && lft < maxd) {
				bit_upd(bit[lft], cur + 1, -1);
				bit_upd(bit[lft], pre + 1, 1);
			}
			if(rht && rht < maxd) {
				bit_upd(bit[rht], cur + 1, -1);
				bit_upd(bit[rht], pre + 1, 1);
			}
			if(lft + rht + 1 < maxd) {
				bit_upd(bit[lft + rht + 1], cur + 1, 1);
				bit_upd(bit[lft + rht + 1], pre + 1, -1);
			}
			for( ; lft < maxd && a[i] - lft - 1 > 0 && pos[a[i] - lft - 1] >= cur; ++lft);
			for( ; rht < maxd && a[i] + rht + 1 < maxn && pos[a[i] + rht + 1] >= cur; ++rht);
		}
		for(pos[a[i]] = i; j <= m && que[j].R == i; ++j)
			for(int k = 1; k < maxd; ++k)
				ans[que[j].idx][k - 1] = '0' + bit_que(bit[k], que[j].L) % mod;
	}
	for(int i = 1; i <= m; ++i)
		puts(ans[i]);
	return 0;
}
