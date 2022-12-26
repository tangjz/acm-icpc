#include <bits/stdc++.h>
using namespace std;
namespace fastIO{
	#define MAXB (1 << 20 | 1)
	bool isEOF = 0;
	inline char next() {
		static char buf[MAXB], *ptr = buf + MAXB, *end = ptr;
		if(ptr == end) {
			ptr = buf;
			end = buf + fread(buf, 1, MAXB, stdin);
			if(ptr == end) {
				isEOF = 1;
				return EOF;
			}
		}
		return *(ptr++);
	}
	inline bool isBlank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void nextChar(char &ch) {
		while(isBlank(ch = next()));
	}
	inline void nextInt(int &x) {
		char ch;
		while(isBlank(ch = next()));
		if(isEOF)
			return;
		bool sign = ch == '-';
		x = sign ? 0 : (ch - '0');
		while((ch = next()) >= '0' && ch <= '9')
			x = x * 10 + (ch - '0');
		if(sign)
			x = -x;
	}
	struct Output {
		char buf[MAXB], *ptr, *end;
		Output() {
			ptr = buf;
			end = buf + MAXB;
		}
		void print(char ch) {
			if(ptr == end) {
				fwrite(buf, 1, MAXB, stdout);
				ptr = buf;
			}
			*(ptr++) = ch;
		}
		void puts(char const buf[]) {
			for(const char *ptr = buf; *ptr; print(*(ptr++)));
			print('\n');
		}
		~Output() {
			if(ptr != buf)
				fwrite(buf, 1, ptr - buf, stdout);
		}
	} out;
	#undef BUF_SIZE
}
const int maxn = (int)3e5 + 1;
int n, m, a[maxn];
struct Node {
	char op;
	int u, v, w;
	void read() {
		fastIO::nextChar(op);
		if(op == 'Q' || op == 'A' || op == 'B' || op == 'D') {
			fastIO::nextInt(u);
			fastIO::nextInt(v);
			if(u > v)
				swap(u, v);
			if(op != 'Q')
				fastIO::nextInt(w);
		} else if(op != 'G') {
			if(op == 'C')
				fastIO::nextInt(u);
			fastIO::nextInt(w);
		}
	}
} que[maxn];
struct Segment {
	int c[3], sft;
	int value() {
		return c[1] | (c[2] << 1);
	}
	void shift(int const &dt) { // dt = 1, 2
		(sft += dt) >= 3 && (sft -= 3);
		if(dt == 1) {
			int t = c[0];
			c[0] = c[2];
			c[2] = c[1];
			c[1] = t;
		} else {
			int t = c[0];
			c[0] = c[1];
			c[1] = c[2];
			c[2] = t;
		}
	}
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_up(Segment &rt, Segment const &lft, Segment const &rht) {
	rt.c[0] = lft.c[0] ^ rht.c[0];
	rt.c[1] = lft.c[1] ^ rht.c[1];
	rt.c[2] = lft.c[2] ^ rht.c[2];
}
void seg_down(Segment &rt, Segment &lft, Segment &rht) {
	if(rt.sft) {
		lft.shift(rt.sft);
		rht.shift(rt.sft);
		rt.sft = 0;
	}
}
void seg_init(int L, int R) {
	int rt = seg_idx(L, R);
	seg[rt].sft = 0;
	if(L == R) {
		seg[rt].c[0] = seg[rt].c[1] = seg[rt].c[2] = 0;
		seg[rt].c[a[L]] = 1;
		return;
	}
	int M = (L + R) >> 1;
	seg_init(L, M);
	seg_init(M + 1, R);
	seg_up(seg[rt], seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
}
void seg_upd(int L, int R, int x, int v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt].c[0] = seg[rt].c[1] = seg[rt].c[2] = 0;
		seg[rt].c[v] = 1;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(seg[rt], seg[lch], seg[rch]);
	if(x <= M)
		seg_upd(L, M, x, v);
	else
		seg_upd(M + 1, R, x, v);
	seg_up(seg[rt], seg[lch], seg[rch]);
}
void seg_sft(int L, int R, int qL, int qR, int dt) {
	int rt = seg_idx(L, R);
	if(qL <= L && R <= qR) {
		seg[rt].shift(dt);
		return;
	}
	int ret = 0, M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(seg[rt], seg[lch], seg[rch]);
	if(qL <= M)
		seg_sft(L, M, qL, qR, dt);
	if(qR > M)
		seg_sft(M + 1, R, qL, qR, dt);
	seg_up(seg[rt], seg[lch], seg[rch]);
}
int seg_que(int L, int R, int qL, int qR) {
	int rt = seg_idx(L, R);
	if(qL <= L && R <= qR)
		return seg[rt].value();
	int ret = 0, M = (L + R) >> 1;
	seg_down(seg[rt], seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
	if(qL <= M)
		ret ^= seg_que(L, M, qL, qR);
	if(qR > M)
		ret ^= seg_que(M + 1, R, qL, qR);
	return ret;
}
int main() {
	fastIO::nextInt(n);
	fastIO::nextInt(m);
	for(int i = 1; i <= n; ++i) {
		fastIO::nextInt(a[i]);
		a[i] %= 3;
	}
	int pL = n + m, pR = 0;
	for(int i = 1; i <= m; ++i) {
		que[i].read();
		if(que[i].op == 'Q') {
			pL = min(pL, que[i].u);
			pR = max(pR, que[i].v);
		}
	}
	if(pL > pR)
		return 0;
	seg_init(pL, pR);
	for(int i = 1; i <= m; ++i) {
		Node &cur = que[i];
		if(cur.op == 'Q') {
			fastIO::out.puts(seg_que(pL, pR, cur.u, cur.v) ? "D" : "B");
		} else if(cur.op == 'A' || cur.op == 'B') {
			int dt = cur.w % 3;
			if(dt && cur.op == 'B')
				dt = 3 - dt;
			if(dt && max(cur.u, pL) <= min(cur.v, pR))
				seg_sft(pL, pR, cur.u, cur.v, dt);
		} else if(cur.op == 'C' || cur.op == 'F') {
			int pos = cur.op == 'C' ? cur.u : (++n), val = cur.w % 3;
			if(pL <= pos && pos <= pR)
				seg_upd(pL, pR, pos, val);
		}
		n -= cur.op == 'G';
	}
	return 0;
}
