#include <bits/stdc++.h>
using namespace std;

const int BLEN = 4 << 20 | 1;

struct FastInput {
	char *pool, *head, *tail;
	bool eof;
 
	FastInput() {
		pool = new char[BLEN];
		head = tail = pool;
		eof = 0;
	}
	~FastInput() {
		delete[] pool;
	}
	char nextChar() {
		if(head == tail) {
			head = pool;
			tail = pool + fread(pool, 1, BLEN, stdin);
			if(head == tail) {
				eof = 1;
				return -1;
			}
		}
		return *(head++);
	}
	void read(int &x) {
		x = 0;
		static char ch, sgn;
		while(isspace(ch = nextChar()));
		if(eof) {
			return;
		}
		(sgn = ch == '-') && (ch = nextChar());
		do x = x * 10 + (ch - '0'); while(isdigit(ch = nextChar()));
		sgn && (x = -x);
	}
} in;

struct FastOutput {
	char *pool, *head, *tail;
 
	FastOutput() {
		pool = new char[BLEN];
		head = pool;
		tail = pool + BLEN;
	}
	~FastOutput() {
		flush();
		delete[] pool;
	}
	void flush() {
		if(head != pool) {
			fwrite(pool, 1, head - pool, stdout);
			head = pool;
		}
	}
	void writeChar(char ch) {
		if(head == tail) {
			fwrite(pool, 1, head - pool, stdout);
			head = pool;
		}
		*(head++) = ch;
	}
	void write(int x) {
		if(!x) {
			writeChar('0');
			return;
		}
		if(x < 0) {
			writeChar('-');
			x = -x;
		}
		static char buf[15], *ptr;
		for(ptr = buf; x; *(ptr++) = '0' + (x % 10), x /= 10);
		for( ; ptr != buf; writeChar(*(--ptr)));
	}
} out;

const int maxn = (int)1e5 + 1, maxm = (int)2e5 + 1, maxe = (int)3e5 + 1;

struct Event {
	int typ, L, R, v;
	void read() {
		// scanf("%d%d", &typ, &L);
		in.read(typ);
		in.read(L);
		if(typ == 2) {
			// scanf("%d", &R);
			in.read(R);
		} else {
			R = L;
		}
		// scanf("%d", &v);
		in.read(v);
	}
} ;

void solve(int n) {
	int m, qtot = 0, etot = 0;
	static int tim = 0, a[maxn], que[maxm], ord[maxe], ans[maxe];
	static pair<int, int> bits[maxm] = {};
	static Event seq[maxe];
	for(int i = 1, v; i <= n; ++i) {
		// scanf("%d", a + i);
		in.read(a[i]);
		seq[etot++] = (Event){1, i, i, a[i]};
		que[qtot++] = a[i];
	}
	// scanf("%d", &m);
	in.read(m);
	while(m--) {
		Event &cur = seq[etot++];
		cur.read();
		if(cur.typ == 2)
			continue;
		if(a[cur.L] == cur.v) {
			--etot;
			continue;
		}
		seq[etot++] = (Event){-1, cur.L, cur.L, a[cur.L]};
		que[qtot++] = a[cur.L] = cur.v;
	}
	sort(que, que + qtot);
	qtot = unique(que, que + qtot) - que;
	for(int i = 0; i < etot; ++i) {
		Event &cur = seq[i];
		if(cur.typ != 2)
			cur.v = lower_bound(que, que + qtot, cur.v) - que;
	}
	iota(ord, ord + etot, 0);
	function<void(int, int, int, int)> calc = [&](int L, int R, int vL, int vR) {
		// printf("calc %d %d %d %d\n", L, R, vL, vR);
		if(L >= R || vL >= vR) {
			for(int i = L; i <= R; ++i) {
				int o = ord[i];
				Event &cur = seq[o];
				if(cur.typ == 2)
					ans[o] = que[vL];
			}
			return;
		}
		int vM = (vL + vR) / 2, M = L, tot = 0;
		static int tim = 0, tmp[maxe];
		if(!(++tim)) {
			memset(bits, 0, sizeof bits);
			++tim;
		}
		for(int i = L; i <= R; ++i) {
			int o = ord[i];
			Event &cur = seq[o];
			// printf("process %d: %d %d %d %d\n", o, cur.typ, cur.L, cur.R, cur.v);
			if(cur.typ != 2) {
				if(cur.v <= vM) {
					for(int x = cur.L; x <= n; x += x & -x) {
						if(bits[x].second == tim) {
							bits[x].first += cur.typ;
						} else {
							bits[x] = {cur.typ, tim};
						}
					}
					ord[M++] = o;
				} else {
					tmp[tot++] = o;
				}
			} else {
				int res = 0;
				for(int x = cur.R; x > 0; x -= x & -x)
					if(bits[x].second == tim)
						res += bits[x].first;
				for(int x = cur.L - 1; x > 0; x -= x & -x)
					if(bits[x].second == tim)
						res -= bits[x].first;
				if(res >= cur.v) {
					ord[M++] = o;
				} else {
					cur.v -= res;
					tmp[tot++] = o;
				}
			}
		}
		memcpy(ord + M, tmp, tot * sizeof(int));
		calc(L, M - 1, vL, vM);
		calc(M, R, vM + 1, vR);
	};
	calc(0, etot - 1, 0, qtot - 1);
	for(int i = 0; i < etot; ++i)
		if(seq[i].typ == 2) {
			out.write(ans[i]);
			out.writeChar('\n');
			// printf("%d\n", ans[i]);
		}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1, n; in.read(n), !in.eof; ++Case) {
		// printf("Case #%d: ", Case);
		solve(n);
	}
	return 0;
}
