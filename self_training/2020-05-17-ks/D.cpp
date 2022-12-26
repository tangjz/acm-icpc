#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
struct Segment {
	int cnt;
	LL sum[2];
	void merge(Segment const &lft, Segment const &rht) {
		cnt = lft.cnt + rht.cnt;
		sum[0] = lft.sum[0] + (lft.cnt & 1 ? -1 : 1) * rht.sum[0];
		sum[1] = lft.sum[1] + (lft.cnt & 1 ? -1 : 1) * (lft.cnt * rht.sum[0] + rht.sum[1]);
	}
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_build(int L, int R) {
	if(L < R) {
		int M = (L + R) >> 1;
		seg_build(L, M);
		seg_build(M + 1, R);
		seg[seg_idx(L, R)].merge(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
	} else {
		int x;
		scanf("%d", &x);
		seg[seg_idx(L, R)] = (Segment){1, (LL)x, (LL)x};
	}
}
void seg_upd(int L, int R, int x, int v) {
	if(L < R) {
		int M = (L + R) >> 1;
		if(x <= M)
			seg_upd(L, M, x, v);
		else
			seg_upd(M + 1, R, x, v);
		seg[seg_idx(L, R)].merge(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
	} else {
		seg[seg_idx(L, R)] = (Segment){1, (LL)v, (LL)v};
	}
}
Segment seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1;
	if(r <= M)
		return seg_que(L, M, l, r);
	if(l > M)
		return seg_que(M + 1, R, l, r);
	Segment ret;
	ret.merge(seg_que(L, M, l, r), seg_que(M + 1, R, l, r));
	return ret;
}
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n, m;
		scanf("%d%d", &n, &m);
		seg_build(1, n);
		LL ans = 0;
		while(m--) {
			char op[3];
			int u, v;
			scanf("%s%d%d", op, &u, &v);
			if(op[0] == 'U') {
				seg_upd(1, n, u, v);
			} else {
				Segment ret = seg_que(1, n, u, v);
				ans += ret.sum[1];
			}
		}
		printf("Case #%d: %lld\n", Case, ans);
	}
	return 0;
}