#include <stdio.h>
#include <algorithm>
const int maxn = 50001;
int n, m, seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_init(int L, int R) {
	int rt = seg_idx(L, R);
	if(L == R) {
		scanf("%d", seg + rt);
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_init(L, M);
	seg_init(M + 1, R);
	seg[rt] = std::max(seg[lch], seg[rch]);
}
void seg_upd(int L, int R, int x) {
	int rt = seg_idx(L, R);
	if(L == R) {
		++seg[rt];
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(seg[lch] >= x || seg[lch] < x && seg[seg_idx(M + 1, M + 1)] >= x)
		seg_upd(L, M, x);
	else
		seg_upd(M + 1, R, x);
	seg[rt] = std::max(seg[lch], seg[rch]);
}
void seg_que(int L, int R) {
	if(L == R) {
		printf("%d\n", seg[seg_idx(L, R)]);
		return;
	}
	int M = (L + R) >> 1;
	seg_que(L, M);
	seg_que(M + 1, R);
}
int main() {
	scanf("%d%d", &n, &m);
	seg_init(1, n);
	while(m--) {
		int x;
		scanf("%d", &x);
		if(x <= seg[seg_idx(1, 1)] || x > seg[seg_idx(1, n)])
			continue;
		seg_upd(1, n, x);
	}
	seg_que(1, n);
	return 0;
}
