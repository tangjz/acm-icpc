#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
const int maxn = (int)1e4 + 1, maxm = (int)1e6 + 1;
const int maxd = 6721, maxe = 13, mod = (int)1e9 + 7;
const int maxd2 = 241, maxq = 101, BLEN = 1 << 20 | 1;
 
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
 
int d[maxm];
 
struct FactorSet {
	LL upp;
	int etot, dtot;
	pair<int, int> pr[maxe]; // (prime, exponent)
	pair<int, int> pre[maxd]; // (prev, div)
	pair<LL, LL> fct[maxd]; // (factor, phi)
	unordered_map<LL, int> idx; // factor -> index
	void dfs(int dep, LL val, LL phi, int las) {
		if(dep == etot) {
			idx.insert({val, dtot});
			pre[dtot] = {idx[val / las], las};
			fct[dtot++] = {val, phi};
			return;
		}
		dfs(dep + 1, val, phi, las);
		for(int i = 1; i <= pr[dep].second; ++i)
			dfs(dep + 1, val *= pr[dep].first, phi *= pr[dep].first - (i == 1), pr[dep].first);
	}
	void generate() {
		dtot = 0;
		idx.clear();
		dfs(0, 1, 1, 1);
	}
public:
	void init(int n, int m = 1) {
		upp = (LL)n * m;
		for(etot = 0; d[n] > 1 || d[m] > 1; ++etot) {
			pr[etot] = {INT_MAX, 0};
			if(d[n] > 1)
				pr[etot].first = min(pr[etot].first, d[n]);
			if(d[m] > 1)
				pr[etot].first = min(pr[etot].first, d[m]);
			for( ; d[n] == pr[etot].first; ++pr[etot].second, n /= d[n]);
			for( ; d[m] == pr[etot].first; ++pr[etot].second, m /= d[m]);
		}
		generate();
	}
} R, C, RC;
 
int modPow(int x, LL k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
 
int modInv(int x) {
	int y = mod, u = 1, v = 0, q;
	while(x) {
		q = y / x;
		tie(x, y) = make_pair(y - q * x, x);
		tie(u, v) = make_pair(v - q * u, u);
	}
	// assert(y == 1);
	return v < 0 ? v + mod : v;
}
 
void solve() {
	int n, r, c;
	static int perm[maxn], ctr[maxn];
	in.read(n);
	in.read(r);
	in.read(c);
	for(int i = 0; i < n; ++i) {
		in.read(perm[i]);
		ctr[i + 1] = 0;
	}
	for(int i = 0; i < n; ++i) {
		if(perm[i] == -1)
			continue;
		int c = 0, j;
		for( ; perm[i] != -1; ++c, j = perm[i], perm[i] = -1, i = j);
		ctr[c] += c;
	}
 
	int qtot = 0;
	static int com[maxd2];
	static pair<LL, int> coeff[maxd];
	R.init(r);
	C.init(c);
	RC.init(r, c);
	for(int i = 0; i < RC.dtot; ++i) {
		LL u = RC.fct[i].first;
		coeff[i] = {};
		if(u <= n)
			coeff[i].second = ctr[u];
	}
	for(int i = 0; i < RC.etot; ++i) {
		int p = RC.pr[i].first;
		for(int j = 0, k = 0; j < RC.dtot; ++j) {
			LL u = RC.fct[j].first;
			if(u % p != 0)
				continue;
			for(LL v = u / p; RC.fct[k].first != v; ++k);
			coeff[j].second += coeff[k].second;
		}
	}
	for(int i = 0; i < R.dtot; ++i)
		for(int j = 0; j < C.dtot; ++j) {
			auto &[u, up] = R.fct[i];
			auto &[v, vp] = C.fct[j];
			auto &[k, p] = C.pre[j];
			com[j] = p > 1 ? (u / com[k] % p == 0 ? com[k] * p : com[k]) : 1;
			int nxt = RC.idx[u / com[j] * v];
			coeff[nxt].first += up * vp;
		}
 
	int ans = 0;
	for(int i = 0; i < RC.dtot; ++i)
		if((coeff[i].first %= mod) && coeff[i].second)
			ans = (ans + coeff[i].first * modPow(coeff[i].second, RC.upp / RC.fct[i].first)) % mod;
	ans = (LL)ans * modInv(RC.upp % mod) % mod;
	printf("%d\n", ans);
}
 
int main() {
	int ptot = 0;
	static int pr[maxm];
	d[1] = 1;
	for(int i = 2; i < maxm; ++i) {
		if(!d[i])
			pr[ptot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxm; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
 
	int T;
	in.read(T);
	for(int Case = 1; Case <= T; ++Case) {
		printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}