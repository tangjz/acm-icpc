#include <queue>
#include <stdio.h>
const int maxn = 1 << 17 | 1, maxs = maxn * 36, INF = (int)2e9 + 1;
int n, m, a[maxn], b[maxn], tot, seg[maxn << 1 | 1], idx[maxs], lch[maxs], rch[maxs];
inline int rng_insert(int u, int L, int R, int x) {
	int rt = ++tot;
	lch[rt] = lch[u];
	rch[rt] = rch[u];
	idx[rt] = b[idx[u]] < b[x] ? idx[u] : x;
	if(L < R) {
		int M = (L + R) >> 1;
		if(a[x] <= M)
			lch[rt] = rng_insert(lch[rt], L, M, x);
		else
			rch[rt] = rng_insert(rch[rt], M + 1, R, x);
	}
	return rt;
}
inline int rng_merge(int u, int v) {
	if(!u || !v)
		return u | v;
	int rt = ++tot;
	lch[rt] = rng_merge(lch[u], lch[v]);
	rch[rt] = rng_merge(rch[u], rch[v]);
	idx[rt] = b[idx[u]] < b[idx[v]] ? idx[u] : idx[v];
	return rt;
}
inline int rng_que(int u, int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return idx[u];
	int M = (L + R) >> 1, ret = 0, tmp;
	if(l <= M) {
		tmp = rng_que(lch[u], L, M, l, r);
		ret = b[ret] < b[tmp] ? ret : tmp;
	}
	if(M < r) {
		tmp = rng_que(rch[u], M + 1, R, l, r);
		ret = b[ret] < b[tmp] ? ret : tmp;
	}
	return ret;
}
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
inline int seg_build(int L, int R) {
	int &rt = seg[seg_idx(L, R)];
	if(L == R) {
		rt = rng_insert(rt, 1, n, L);
	} else {
		int M = (L + R) >> 1;
		rt = rng_merge(seg_build(L, M), seg_build(M + 1, R));
	}
	return rt;
}
inline int seg_que(int L, int R, int l, int r, int u, int d) {
	if(l <= L && R <= r)
		return rng_que(seg[seg_idx(L, R)], 1, n, u, d);
	int M = (L + R) >> 1, ret = 0, tmp;
	if(l <= M) {
		tmp = seg_que(L, M, l, r, u, d);
		ret = b[ret] < b[tmp] ? ret : tmp;
	}
	if(M < r) {
		tmp = seg_que(M + 1, R, l, r, u, d);
		ret = b[ret] < b[tmp] ? ret : tmp;
	}
	return ret;
}
int seq[maxn][5];
struct Node {
	int sum, id, L, R, D, U;
	bool operator < (Node const &t) const {
		return sum > t.sum;
	}
} ;
std::priority_queue<Node> Q;
namespace fastIO {
	#define BUF_SIZE (5 << 20 | 1)
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	#undef BUF_SIZE
};
int main() {
	fastIO::read(n), fastIO::read(m);
	for(int i = 1; i <= n; ++i) {
		fastIO::read(a[i]), fastIO::read(b[i]);
		Q.push((Node){b[i], i, i, i, a[i], a[i]});
	}
	b[0] = INF;
	seg_build(1, n);
	for(int i = 1; i <= n; ++i) {
		seq[i][0] = -1;
		fastIO::read(seq[i][1]), fastIO::read(seq[i][2]), fastIO::read(seq[i][3]), fastIO::read(seq[i][4]);
	}
	int ans = 0;
	for(int i = 1; i <= m; ++i) {
		Node cur = Q.top();
		Q.pop();
		ans = cur.sum;
		int jd = seq[cur.id][0];
		if(jd < 0)
			jd = seq[cur.id][0] = seg_que(1, n, seq[cur.id][1], seq[cur.id][2], seq[cur.id][3], seq[cur.id][4]);
		if(jd && cur.sum + b[jd] < INF)
			Q.push((Node){cur.sum + b[jd], jd, seq[cur.id][1], seq[cur.id][2], seq[cur.id][3], seq[cur.id][4]});
		if(cur.L < cur.id) {
			jd = seg_que(1, n, cur.L, cur.id - 1, cur.D, cur.U);
			if(jd && cur.sum - b[cur.id] + b[jd] < INF)
				Q.push((Node){cur.sum - b[cur.id] + b[jd], jd, cur.L, cur.id - 1, cur.D, cur.U});
		}
		if(cur.id < cur.R) {
			jd = seg_que(1, n, cur.id + 1, cur.R, cur.D, cur.U);
			if(jd && cur.sum - b[cur.id] + b[jd] < INF)
				Q.push((Node){cur.sum - b[cur.id] + b[jd], jd, cur.id + 1, cur.R, cur.D, cur.U});
		}
	}
	printf("%d\n", ans);
	return 0;
}
