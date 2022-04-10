#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)1e5 + 9, maxm = (int)1e6 + 9;
const int maxl = 100 + 9, maxs = (int)5e5 + 9;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

inline void modInc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}

struct Hash {
	int mod, seed;
	vector<int> pw, hh;
	Hash(int m, int s) : mod(m), seed(s), pw({1}), hh({0}) {}
	void parse(int n, char s[]) {
		pw.reserve(n + 1);
		hh.reserve(n + 1);
		while((int)pw.size() <= n)
			pw.push_back((LL)pw.back() * seed % mod);
		hh.resize(1);
		for(int i = 0; i < n; ++i) {
			int o = s[i] - 'a' + 1;
			hh.push_back(((LL)hh.back() * seed + o) % mod);
		}
	}
	int get(int L, int R) {
		int ret = (hh[R + 1] - (LL)hh[L] * pw[R - L + 1]) % mod;
		return ret < 0 ? (ret + mod) : ret;
	}
} ;

struct Hash2 {
	static const int mod0 = (int)1e9 + 7, seed0 = 37;
	static const int mod1 = (int)1e9 + 403, seed1 = 29;
	Hash h0, h1;
	Hash2() : h0(mod0, seed0), h1(mod1, seed1) {}
	void parse(int n, char s[]) {
		h0.parse(n, s);
		h1.parse(n, s);
	}
	ULL get(int L, int R) {
		return (ULL)h0.get(L, R) << 32 | (ULL)h1.get(L, R);
	}
} ;

void solve() {
	int n, q;
	static char buf[maxn], pat[maxl];
	scanf("%d%d%s%s", &n, &q, pat, buf);

	static int pw2[maxn], ipw2[maxn], cnt[maxc + 1][maxn];
	pw2[0] = ipw2[0] = 1;
	pw2[1] = 2;
	ipw2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= n; ++i) {
		pw2[i] = (LL)pw2[i - 1] * pw2[1] % mod;
		ipw2[i] = (LL)ipw2[i - 1] * ipw2[1] % mod;
	}
	for(int i = 0; i < maxc; ++i)
		cnt[i][0] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < maxc; ++j)
			cnt[j][i] = cnt[j][i - 1];
		int o = buf[i - 1] - 'a';
		modInc(cnt[o][i], ipw2[i]);
	}

	int len = strlen(pat);
	int upp = ((int)1e6 - 1) / (len + 1) + 1;
	if(n <= 20)
		upp = min(upp, (1 << n) - 1);
	static int pL[maxs];
	static char seq[maxs];
	pL[0] = 1;
	for(int i = 1, mx = 0; i <= upp; ++i) {
		for( ; i >= (1 << mx); ++mx);
		pL[i] = mx + 1;
		int j = __builtin_ctz(i);
		seq[i - 1] = buf[j];
	}
	Hash2 A, B, C, D, E;
	A.parse(len, pat);
	C.parse(n, seq);

	while(q--) {
		int qR;
		static char que[maxm];
		scanf("%d%s", &qR, que);
		int qLen = strlen(que);
		static bool ban[maxl];
		memset(ban, 0, (len + 1) * sizeof(bool));
		for(int i = 0, j = 0; i < qLen; ++i, (++j) == len + 1 && (j = 0))
			if(que[i] != que[j]) {
				ban[j] = 1;
			}

		B.parse(min(qLen, len + 1), que);
		int ans = 0, matched = 0;
		for(int i = 0; i < len; ++i)
			matched += !ban[i];
		for(int L = 0, R = len - 1; L <= len; ++L, (++R) > len && (R = 0)) {
			if(L > 0) {
				matched -= !ban[L - 1];
				matched += !ban[R];
			}
			if(matched != len)
				continue;
			if(L <= R) {
				if(L < qLen) {
					int realR = min(R, qLen - 1);
					if(A.get(0, realR - L) != B.get(L, realR))
						continue;
				}
			} else {
				int pos = len - L + 1;
				if(L < qLen) {
					int realR = min(len, qLen - 1);
					if(A.get(0, realR - L) != B.get(L, realR))
						continue;
				}
				int realR = min(R, qLen - 1);
				if(A.get(pos, pos + realR) != B.get(0, realR))
					continue;
			}

			int m = 0;
			static char adt[maxs];
			for(int j = L - 1; j < qLen; j += len + 1)
				if(j >= 0)
					adt[m++] = que[j];
			if(!m) {
				modInc(ans, 1);
				continue;
			}
			if(m > upp || pL[m >> 1] > qR)
				continue;
			D.parse(m, adt);
			reverse(adt, adt + m);
			E.parse(m, adt);
			reverse(adt, adt + m);
			for(int j = 0; j < m; ++j) {
				int lft = j, rht = m - j - 1;
				int qL = pL[max(lft, rht)];
				if(qL > qR)
					continue;
				if(lft && C.get(0, lft - 1) != E.get(m - j, m - 1))
					continue;
				if(rht && C.get(0, rht - 1) != D.get(j + 1, m - 1))
					continue;
				int o = adt[j] - 'a';
				modInc(ans, cnt[o][qR] - cnt[o][qL - 1]);
				ans < 0 && (ans += mod);
			}
		}
		ans = (LL)ans * pw2[qR] % mod;
		printf("%d\n", ans);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}