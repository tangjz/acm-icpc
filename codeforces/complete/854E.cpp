#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = (int)2e5 + 1, maxm = maxn * 21;
int n, q, a[maxn], seg_tot, root[maxn];
struct Segment {
	int cnt, lch, rch;
} seg[maxm];
void update(int &rt, int L, int R, int x) {
	int last = rt;
	seg[rt = ++seg_tot] = seg[last];
	++seg[rt].cnt;
	if(L == R)
		return;
	int M = (L + R) >> 1;
	if(x <= M)
		update(seg[rt].lch, L, M, x);
	else
		update(seg[rt].rch, M + 1, R, x);
}
int query(int rt, int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[rt].cnt;
	int M = (L + R) >> 1;
	if(r <= M)
		return query(seg[rt].lch, L, M, l, r);
	if(M < l)
		return query(seg[rt].rch, M + 1, R, l, r);
	return query(seg[rt].lch, L, M, l, r) + query(seg[rt].rch, M + 1, R, l, r);
}
int query(int xL, int xR, int yL, int yR) {
	return query(root[xR], 1, n, yL, yR) - query(root[xL - 1], 1, n, yL, yR);
}
inline LL sum2(int x) {
	return (x * (x - 1LL)) >> 1;
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		root[i] = root[i - 1];
		update(root[i], 1, n, a[i]);
	}
	while(q--) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		int all = n;
		int hor1 = 1 < y1 ? query(1, n, 1, y1 - 1) : 0;
		int hor2 = y2 < n ? query(1, n, y2 + 1, n) : 0;
		int ver1 = 1 < x1 ? query(1, x1 - 1, 1, n) : 0;
		int ver2 = x2 < n ? query(x2 + 1, n, 1, n) : 0;
		int squ11 = 1 < x1 && 1 < y1 ? query(1, x1 - 1, 1, y1 - 1) : 0;
		int squ12 = 1 < x1 && y2 < n ? query(1, x1 - 1, y2 + 1, n) : 0;
		int squ21 = x2 < n && 1 < y1 ? query(x2 + 1, n, 1, y1 - 1) : 0;
		int squ22 = x2 < n && y2 < n ? query(x2 + 1, n, y2 + 1, n) : 0;
		printf("%I64d\n", sum2(all) - sum2(hor1) - sum2(hor2) - sum2(ver1) - sum2(ver2) + sum2(squ11) + sum2(squ12) + sum2(squ21) + sum2(squ22));
	}
	return 0;
}
