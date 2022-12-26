#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 9;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
struct Fenwick {
	int len, mx, que[maxn], cnt[maxn];
	LL sum[maxn];
	void init(int n, int arr[]) {
		len = n;
		memcpy(que, arr, len * sizeof(int));
		sort(que, que + len);
		len = unique(que, que + len) - que;
		memset(cnt, 0, (len + 1) * sizeof(int));
		memset(sum + 1, 0, len * sizeof(LL));
		for(mx = 1; mx <= len; mx <<= 1);
		mx >>= 1;
	}
	void update(int x, int v) {
		LL vx = v * x;
		x = lower_bound(que, que + len, x) - que + 1;
		cnt[0] += v;
		for( ; x <= len; x += x & -x) {
			cnt[x] += v;
			sum[x] += vx;
		}
	}
	LL lowest(int k) {
		if(k > cnt[0])
			return INF;
		int x = 0;
		LL ret = 0;
		for(int y = mx, z; y; y >>= 1)
			if((z = x | y) <= len && cnt[z] < k) {
				x = z;
				k -= cnt[z];
				ret += sum[z];
			}
		return ret + que[x] * k;
	}
} lft, rht;
int t, n, m;
pair<int, int> seq[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &m, &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", &seq[i].first);
		for(int i = 0; i < n; ++i)
			scanf("%d", &seq[i].second);
		sort(seq, seq + n);
		static int tmp[maxn];
		for(int i = 0; i < n; ++i)
			tmp[i] = seq[i].second - seq[i].first;
		lft.init(n, tmp);
		for(int i = 0; i < n; ++i)
			tmp[i] = seq[i].second + seq[i].first;
		rht.init(n, tmp);
		for(int i = 0; i < n; ++i)
			rht.update(tmp[i], 1);
		LL ans = INF;
		for(int i = 0; i < n; ++i) {
			rht.update(seq[i].second + seq[i].first, -1);
			int L = max(m - rht.cnt[0], 0), R = min(lft.cnt[0], m);
			while(R - L + 1 >= 6) {
				int step = (R - L + 1) / 3;
				int ML = L + step, MR = R - step;
				LL fL = (LL)(ML + ML - m) * seq[i].first + lft.lowest(ML) + rht.lowest(m - ML);
				LL fR = (LL)(MR + MR - m) * seq[i].first + lft.lowest(MR) + rht.lowest(m - MR);
				if(fL <= fR) {
					R = MR;
				} else {
					L = ML;
				}
			}
			for( ; L <= R; ++L) {
				LL tmp = (LL)(L + L - m) * seq[i].first + lft.lowest(L) + rht.lowest(m - L);
				ans = min(ans, tmp + seq[i].second);
			}
			lft.update(seq[i].second - seq[i].first, 1);
		}
		printf("Case #%d: %lld\n", Case, ans);
	}
	return 0;
}
