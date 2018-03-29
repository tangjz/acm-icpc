#include <bits/stdc++.h>
const int maxn = (int)1e5 + 1, maxm = maxn * 17;
int n, m, a[maxn], qtot, que[maxn], stot, rt[maxn], lch[maxm], rch[maxm], sum[maxm];
void seg_upd(int &cur, int L, int R, int v) {
	int las = cur;
	cur = ++stot;
	lch[cur] = lch[las];
	rch[cur] = rch[las];
	sum[cur] = sum[las] + v;
	if(L == R)
		return;
	int M = (L + R) >> 1;
	if(v <= que[M])
		seg_upd(lch[cur], L, M, v);
	else if(v >= que[M + 1])
		seg_upd(rch[cur], M + 1, R, v);
}
int seg_que(int pre, int cur, int L, int R, int v) {
	if(que[R] <= v)
		return sum[cur] - sum[pre];
	int M = (L + R) >> 1;
	return seg_que(lch[pre], lch[cur], L, M, v) + (que[M + 1] <= v ? seg_que(rch[pre], rch[cur], M + 1, R, v) : 0);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		que[i - 1] = a[i];
	}
	std::sort(que, que + n);
	qtot = std::unique(que, que + n) - que;
	for(int i = 1; i <= n; ++i) {
		rt[i] = rt[i - 1];
		seg_upd(rt[i], 0, qtot - 1, a[i]);
	}
	scanf("%d", &m);
	while(m--) {
		int L, R, ans = 0, low;
		scanf("%d%d", &L, &R);
		do {
			low = ans + 1;
			ans = seg_que(rt[L - 1], rt[R], 0, qtot - 1, low);
		} while(ans >= low);
		printf("%d\n", low);
	}
	return 0;
}
