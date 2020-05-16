#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)3e5 + 1, maxd = 30, maxv = (int)1e9, INF = 0x3f3f3f3f;
int n, m, upp[maxn], seg[maxn << 1 | 1], ord[maxn];
struct Info {
	int typ, x, y, z;
} que[maxn];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_dfs(int L, int R, int v = INF) {
	int rt = seg_idx(L, R);
	v = min(v, seg[rt]);
	if(L == R) {
		if(upp[L] == -1)
			upp[L] = v;
		seg[rt] = upp[L];
	} else {
		int M = (L + R) >> 1;
		seg_dfs(L, M, v);
		seg_dfs(M + 1, R, v);
		seg[rt] = max(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
	}
}
void seg_upd(int L, int R, int l, int r, int v, bool ass = 0) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r) {
		seg[rt] = ass ? v : min(seg[rt], v);
	} else {
		int M = (L + R) >> 1;
		if(l <= M)
			seg_upd(L, M, l, r, v, ass);
		if(r > M)
			seg_upd(M + 1, R, l, r, v, ass);
		if(ass)
			seg[rt] = max(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
	}
}
int seg_que(int L, int R, int x) {
	int ret = seg[seg_idx(x, x)];
	while(L < R) {
		ret = min(ret, seg[seg_idx(L, R)]);
		int M = (L + R) >> 1;
		if(x <= M) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	return ret;
}
int seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1;
	int lft = l <= M ? seg_que(L, M, l, r) : 0;
	int rht = r > M ? seg_que(M + 1, R, l, r) : 0;
	return max(lft, rht);
}
int main() {
	scanf("%d%d", &n, &m);
	memset(upp + 1, -1, n * sizeof(int));
	memset(seg + 1, 0x3f, (n << 1) * sizeof(int));
	for(int i = 1; i <= m; ++i) {
		Info &cur = que[i];
		scanf("%d%d%d", &cur.typ, &cur.x, &cur.y);
		if(cur.typ == 1) {
			scanf("%d", &cur.z);
			seg_upd(1, n, cur.x, cur.y, cur.z);
		} else if(upp[cur.x] == -1) {
			upp[cur.x] = seg_que(1, n, cur.x);
		}
	}
	seg_dfs(1, n);
	for(int i = 1; i <= m; ++i) {
		Info &cur = que[i];
		if(cur.typ != 1) {
			seg_upd(1, n, cur.x, cur.x, cur.y, 1);
		} else if(seg_que(1, n, cur.x, cur.y) != cur.z) {
			puts("NO");
			return 0;
		}
	}
	for(int i = 1; i <= n; ++i)
		ord[i] = i;
	sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
		return upp[u] < upp[v];
	});
	int ans = 0;
	for(int i = 1; i <= n; ) {
		int val = upp[ord[i]], adt;
		if(val < INF) {
			ans |= val;
			for(adt = 0; (adt << 1 | 1) <= val; adt = adt << 1 | 1);
		} else {
			adt = 0;
			for(int j = 1 << (maxd - 1); j; j >>= 1)
				if(!(ans & j) && (adt | j) <= maxv)
					adt |= j;
			upp[ord[i]] = adt;
			ans |= adt;
			adt = ((1 << maxd) - 1) ^ ans;
		}
		for(++i; i <= n && upp[ord[i]] == val; ++i) {
			upp[ord[i]] = adt;
			ans |= adt;
		}
	}
	puts("YES");
	for(int i = 1; i <= n; ++i)
		printf("%d%c", upp[i], " \n"[i == n]);
	return 0;
}