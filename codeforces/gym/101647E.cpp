#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = 500001, INF = 0x3f3f3f3f;
int rad, n, totL, totR;
struct Query {
	int typ, x, y;
} que[maxn];
struct Fraction {
	LL x, y;
	Fraction() {}
	Fraction(LL _x, LL _y) { // _y > 0
		LL r = __gcd(abs(_x), _y);
		x = _x / r;
		y = _y / r;
	}
	bool operator == (Fraction const &t) const {
		return x == t.x && y == t.y;
	}
	bool operator < (Fraction const &t) const {
		return (DB)x * t.y < (DB)t.x * y;
	}
} pL[maxn], pR[maxn], seqL[maxn], seqR[maxn];
int cnt, idx[maxn], ord[maxn], pos[maxn], seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int x, int v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt] = v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		seg_upd(L, M, x, v);
	else
		seg_upd(M + 1, R, x, v);
	seg[rt] = min(seg[lch], seg[rch]);
}
int seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1, ret = INF;
	if(l <= M)
		ret = min(ret, seg_que(L, M, l, r));
	if(M < r)
		ret = min(ret, seg_que(M + 1, R, l, r));
	return ret;
}
inline int sgn(int x) {
	return (x > 0) - (x < 0);
}
inline LL sqr(int x) {
	return (LL)x * x;
}
bool cmp(int const &u, int const &v) {
	return que[u].x < que[v].x;
}
int main() {
	scanf("%d%d", &rad, &n);
	for(int i = 1; i <= n; ++i) {
		int &typ = que[i].typ, &x = que[i].x, &y = que[i].y;
		scanf("%d%d", &typ, &x);
		if(typ != 2)
			scanf("%d", &y);
		if(typ != 1)
			continue;
		LL A = sqr(rad + x), B = sqr(rad - x), C = sqr(y);
		seqL[++totL] = pL[i] = Fraction(sgn(rad + x) * A, A + C);
		seqR[++totR] = pR[i] = Fraction(sgn(rad - x) * B, B + C);
	}
	sort(seqL + 1, seqL + totL + 1);
	totL = unique(seqL + 1, seqL + totL + 1) - seqL - 1;
	sort(seqR + 1, seqR + totR + 1);
	totR = unique(seqR + 1, seqR + totR + 1) - seqR - 1;
	for(int i = 1; i <= n; ++i) {
		int &typ = que[i].typ, &x = que[i].x, &y = que[i].y;
		if(typ == 1) {
			int px = x, py = y;
			x = lower_bound(seqL + 1, seqL + totL + 1, pL[i]) - seqL;
			y = lower_bound(seqR + 1, seqR + totR + 1, pR[i]) - seqR;
			pL[i] = px >= -rad ? Fraction(sqr(px + rad) - sqr(py), sqr(px + rad) + sqr(py)) : Fraction(-1, 1);
			pR[i] = px <= rad ? Fraction(sqr(py) - sqr(px - rad), sqr(px - rad) + sqr(py)) : Fraction(1, 1);
			ord[++cnt] = i;
			idx[cnt] = i;
		}
	}
	sort(ord + 1, ord + cnt + 1, cmp);
	for(int i = 1; i <= cnt; ++i)
		pos[ord[i]] = i;
	static bool vis[maxn] = {};
	memset(seg + 1, 0x3f, (cnt << 1) * sizeof(int));
	for(int i = 1; i <= n; ++i) {
		int &typ = que[i].typ, &x = que[i].x, &y = que[i].y;
		if(typ == 1) {
			vis[i] = 1;
			// printf("ins %d: %d %d\n", pos[i], que[i].x, que[i].y);
			seg_upd(1, cnt, pos[i], que[i].y);
		} else if(typ == 2) {
			x = idx[x];
			assert(vis[x] == 1);
			// printf("rem %d: %d %d\n", pos[x], que[x].x, que[x].y);
			seg_upd(1, cnt, pos[x], INF);
			vis[x] = 0;
		} else {
			x = idx[x], y = idx[y];
			assert(vis[x] == 1 && vis[y] == 1);
			// printf("ask (%d, %d) (%d, %d)\n", que[x].x, que[x].y, que[y].x, que[y].y);
			if(min(pR[x], pR[y]) < max(pL[x], pL[y])) {
				puts("NO");
				continue;
			}
			int A = max(que[x].x, que[y].x), B = max(que[x].y, que[y].y);
			seg_upd(1, cnt, pos[x], INF);
			seg_upd(1, cnt, pos[y], INF);
			que[0] = (Query){0, A};
			int id = upper_bound(ord + 1, ord + cnt + 1, 0, cmp) - ord - 1;
			// printf("query [%d, %d]\n", 1, id);
			puts(seg_que(1, cnt, 1, id) > B ? "YES" : "NO");
			seg_upd(1, cnt, pos[x], que[x].y);
			seg_upd(1, cnt, pos[y], que[y].y);
		}
	}
	return 0;
}
