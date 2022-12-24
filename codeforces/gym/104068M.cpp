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

typedef long long LL;
const int maxLen = 20, maxm = 1 << maxLen | 1, maxd = 19;
const int mod = 998244353, gen = 3;

int w[maxm << 1 | 1];
void initNTT(int len) {
	assert(len < maxm && (mod - 1) % len == 0);
	int *W = w + len;
	W[1] = W[0] = 1;
	for(int i = (mod - 1) / len, x = gen; i > 0; i >>= 1, x = (LL)x * x % mod)
		if(i & 1)
			W[1] = (LL)W[1] * x % mod;
    for(int i = 2; i < len; ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int i = len - 1; i > 0; --i)
		w[i] = w[i << 1];
}
inline int modAdd(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
}
inline int modSub(int x, int y) {
	return (x -= y) < 0 ? (x + mod) : x;
}
void NTT(int n, int a[], int flag) {
	int i, j, k;
	for(i = 1, j = 0; i < n; ++i) {
		for(k = n >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			swap(a[i], a[j]);
	}
	int *W = w + 1, t;
	for(i = 1; i < n; i <<= 1)
		for(j = 0, W += i; j < n; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = (LL)W[k] * a[i + j + k] % mod;
				a[i + j + k] = modSub(a[j + k], t);
				a[j + k] = modAdd(a[j + k], t);
			}
    if(flag != -1)
        return;
    reverse(a + 1, a + n);
	for(i = 1, j = 1; i < n; i <<= 1)
		j = (j & 1 ? mod + j : j) >> 1;
    for(i = 0; i < n; ++i)
		a[i] = (LL)a[i] * j % mod;
}

struct Node {
	int idx, val, ofs;
	bool operator < (Node const &t) const {
		return val < t.val || (val == t.val && ofs > t.ofs);
	}
};
void solve() {
	int n = 0, m, tot = 1;
	static Node dim[maxd];
	// scanf("%d", &m);
	in.read(m);
	for(int i = 1; i <= m; ++i) {
		// scanf("%d", &dim[n].val);
		in.read(dim[n].val);
		if(dim[n].val == 1)
			continue;
		dim[n].idx = i;
		dim[n].ofs = tot;
		tot *= dim[n++].val;
	}
	if(n <= 1) {
		for(int i = 0; i < tot; ++i) {
			// printf("1%c", " \n"[i == tot - 1]);
			out.writeChar('1');
			out.writeChar(" \n"[i == tot - 1]);
		}
		return;
	}
	sort(dim, dim + n);
	--n; // dim -- [0, n): force, n: conv
	assert(n < maxd);
	int len = 1, las = dim[n].val, rem = tot / las;
	for( ; len < las * 2 - 1 || len < las; len <<= 1);
	assert(len * rem < (maxm << 1 | 1));
	initNTT(len);

	static int a[maxd]; // high to low
	static int coe[maxd][maxd][maxm >> 1 | 1], f[maxd][maxm << 1 | 1], g[maxm];
	for(int i = 0; i <= n; ++i) // dim
		for(int j = 0; j < las; ++j) { // val
			int &prd = coe[1][i][j] = (coe[0][i][j] = 1), x = j + 1;
			for(int k = dim[i].idx; k > 0; k >>= 1, x = (LL)x * x % mod)
				if(k & 1)
					prd = (LL)prd * x % mod;
		}
	for(int i = 2; i <= n; ++i) // exp
		for(int j = 0; j <= n; ++j) // dim
			for(int k = 0; k < las; ++k) // val
				coe[i][j][k] = (LL)coe[i - 1][j][k] * coe[i - 1][j][k] % mod * coe[1][j][k] % mod;
	memset(a, 0, n * sizeof(int));
	for(int i = 0; i < rem; ++i) {
		// next iter
		int u = 0, cN = 0, cU = 0;
		if(i > 0)
			++a[n - 1];
		for(int j = n - 1; j >= 0; --j) {
			if(j && a[j] == dim[j].val) {
				a[j] = 0;
				++a[j - 1];
			}
			u += dim[j].ofs * a[j];
			cN += a[j] > 0;
			cU += a[j] + 1 == dim[j].val;
		}
		// gather-reduce
		int adt = 0, *F = f[0] + i * len, *G, *H;
		function<void(int, int, int, int, int)> dfs = [&](int dep, int lft, int rht, int c0, int c1) {
			if(dep == n) {
				assert(lft < rem && rht < rem);
				if(cN > 1 && c0) {
					G = f[0] + lft * len;
					H = f[0] + rht * len;
					adt = (adt + (LL)c0 * G[0] % mod * H[0]) % mod;
				}
				if(c1) {
					G = f[cN] + lft * len;
					H = f[cN] + rht * len;
					for(int j = 0; j < len; ++j)
						F[j] = (F[j] + (LL)c1 * G[j] % mod * H[j]) % mod;
				}
				return;
			}
			int upp = a[dep], ofs = dim[dep].val;
			if(!upp) {
				dfs(dep + 1, lft * ofs, rht * ofs, c0, c1);
				return;
			}
			for(int j = 0, k = upp - 1; j < upp; ++j, --k)
				dfs(
					dep + 1,
					lft * ofs + j,
					rht * ofs + k,
					cN > 1 ? (LL)c0 * coe[cN - 1][dep][j] % mod * coe[cN - 1][dep][k] % mod : 1,
					(LL)c1 * coe[cN][dep][j] % mod * coe[cN][dep][k] % mod
				);
		};
		if(cN > 0) {
			memset(F, 0, len * sizeof(LL));
			dfs(0, 0, 0, 1, 1);
			NTT(len, F, -1);
			memset(F + las, 0, (len - las) * sizeof(int));
			for(int j = las - 1, k = u + dim[n].ofs * j; j > 0; --j, k -= dim[n].ofs)
				g[k] = (F[j] = F[j - 1]);
			g[u] = F[0] = cN > 1 ? adt : 1;
		} else {
			memset(F + las, 0, (len - las) * sizeof(int));
			for(int j = las - 1, k = u + dim[n].ofs * j; j >= 0; --j, k -= dim[n].ofs)
				g[k] = F[j] = 1;
		}
		// spread
		// if(!cU)
			for(int j = 1; j <= n; ++j) {
				G = f[j] + i * len;
				for(int k = 0; k < las; ++k)
					G[k] = (LL)F[k] * coe[j][n][k] % mod;
				memset(G + las, 0, (len - las) * sizeof(int));
				NTT(len, G, 1);
			}
	}
	for(int i = 0; i < tot; ++i) {
		// printf("%d%c", g[i], " \n"[i == tot - 1]);
		assert(g[i] >= 0);
		out.write(g[i]);
		out.writeChar(" \n"[i == tot - 1]);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	in.read(T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}