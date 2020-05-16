#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1;
char buf[maxn];
int t, n, ctr[maxn];
class SuffixArray {
private:
	bool typ[maxn << 1 | 1];
	int seq[maxn << 1 | 1], pos[maxn], *cur;
	void solve(int n, int m, int seq[], bool typ[], int pos[]) {
		int n1 = typ[n - 1] = 0;
		int ch = rk[0] = -1;
		int *seq1 = seq + n;
		auto inducedSort = [&](int v[]) {
			memset(sa, -1, n * sizeof(int));
			memset(ctr, 0, m * sizeof(int));
			for(int i = 0; i < n; ++i)
				++ctr[seq[i]];
			for(int i = 1; i < m; ++i)
				ctr[i] += ctr[i - 1];
			for(int i = 0; i < m; ++i)
				cur[i] = ctr[i] - 1;
			for(int i = n1 - 1; i >= 0; --i)
				sa[cur[seq[v[i]]]--] = v[i];
			for(int i = 1; i < m; ++i)
				cur[i] = ctr[i - 1];
			for(int i = 0; i < n; ++i)
				if(sa[i] > 0 && typ[sa[i] - 1])
					sa[cur[seq[sa[i] - 1]]++] = sa[i] - 1;
			for(int i = 0; i < m; ++i)
				cur[i] = ctr[i] - 1;
			for(int i = n - 1; i >= 0; --i)
				if(sa[i] > 0 && !typ[sa[i] - 1])
					sa[cur[seq[sa[i] - 1]]--] = sa[i] - 1;
		};
		for(int i = n - 2; i >= 0; --i)
			typ[i] = seq[i] == seq[i + 1] ? typ[i + 1] : (seq[i] > seq[i + 1]);
		for(int i = 1; i < n; ++i)
			if(typ[i - 1] && !typ[i]) {
				pos[n1] = i;
				rk[i] = n1++;
			} else {
				rk[i] = -1;
			}
		inducedSort(pos);
		for(int i = 0, x, y; i < n; ++i) {
			x = rk[sa[i]];
			if(x < 0)
				continue;
			if(ch < 1 || pos[x + 1] - pos[x] != pos[y + 1] - pos[y]) {
				++ch;
			} else {
				for(int j = pos[x], k = pos[y]; j <= pos[x + 1]; ++j, ++k)
					if((seq[j] << 1 | typ[j]) != (seq[k] << 1 | typ[k])) {
						++ch;
						break;
					}
			}
			y = x;
			seq1[y] = ch;
		}
		if(ch + 1 < n1) {
			solve(n1, ch + 1, seq1, typ + n, pos + n1);
		} else {
			for(int i = 0; i < n1; ++i)
				sa[seq1[i]] = i;
		}
		for(int i = 0; i < n1; ++i)
			seq1[i] = pos[sa[i]];
		inducedSort(seq1);
	}
public:
	int sa[maxn], rk[maxn], ht[maxn];
	void init(int len, char buf[]) {
		int m = 256;
		memset(ctr, 0, m * sizeof(int));
		for(int i = 0; i <= n; ++i)
			ctr[buf[i]] = 1;
		for(int i = 1; i < m; ++i)
			ctr[i] += ctr[i - 1];
		for(int i = 0; i <= n; ++i)
			seq[i] = ctr[buf[i]] - 1;
		cur = ht;
		solve(n + 1, ctr[m - 1], seq, typ, pos);
		rotate(sa, sa + 1, sa + n + 1);
		for(int i = 0; i < n; ++i)
			rk[sa[i]] = i;
		for(int i = 0, dt = 0; i < n; ++i) {
			dt -= dt > 0;
			if(rk[i])
				for(int j = sa[rk[i] - 1]; buf[i + dt] == buf[j + dt]; ++dt);
			ht[rk[i]] = dt;
		}
	}
} suf;
int Log[maxn], rk2[maxn];
class SparseTable {
private:
	static const int maxl = 4, maxg = 14;
	static const int maxm = (maxn - 1) / 15 + 1, INF = ~0u >> 1;
	int length, size, blocks;
	int local[maxl | 1][maxn], global[maxg | 1][maxm];
	int getLocal(int L, int R) {
		int d = Log[R - L + 1];
		return min(local[d][L], local[d][R - (1 << d) + 1]);
	}
	int getGlobal(int pL, int pR) {
		int d = Log[pR - pL + 1];
		return min(global[d][pL], global[d][pR - (1 << d) + 1]);
	}
public:
	void init(int len, int arr[]) {
		length = len;
		size = min(max(Log[length], 1), 15);
		for(int i = blocks = 0; i < len; i += size, ++blocks) {
			int adt = min(len - i, size);
			int &low = global[0][blocks] = INF;
			for(int j = i; j < i + adt; ++j)
				low = min(low, local[0][j] = arr[j]);
			for(int j = 1, dt = 1; dt + dt <= adt; ++j, dt <<= 1)
				for(int k = i, kLim = i + adt - dt - dt; k <= kLim; ++k)
					local[j][k] = min(local[j - 1][k], local[j - 1][k + dt]);
		}
		for(int i = 1, dt = 1; dt + dt <= blocks; ++i, dt <<= 1)
			for(int j = 0, jLim = blocks - dt - dt; j <= jLim; ++j)
				global[i][j] = min(global[i - 1][j], global[i - 1][j + dt]);
	}
	int query(int L, int R) { // [L, R]
		int pL = L / size, pR = R / size;
		if(pL == pR)
			return getLocal(L, R);
		int ret = min(getLocal(L, (pL + 1) * size - 1), getLocal(pR * size, R));
		return pR - pL < 2 ? ret : min(ret, getGlobal(pL + 1, pR - 1));
	}
} st, st2, sp;
inline int lcp(int L, int R) { // [L, R]
	if(L == n || R == n)
		return 0;
	if(L == R)
		return n - L;
	L = suf.rk[L];
	R = suf.rk[R];
	if(L > R)
		swap(L, R);
	return st.query(L + 1, R);
}
inline int lcs(int L, int R) { // [L, R]
	if(L < 0 || R < 0)
		return 0;
	if(L == R)
		return L + 1;
	L = rk2[L];
	R = rk2[R];
	if(L > R)
		swap(L, R);
	return st2.query(L + 1, R);
}
inline int lsr(int L, int R) { // [L, R)
	return suf.sa[sp.query(L, R - 1)];
}
typedef long long LL;
class HashTable {
private:
	static const int mod1 = (int)1e9 + 7, mod2 = (int)1e9 + 9, seed = 27;
	int pw1[maxn], pw2[maxn], hh1[maxn], hh2[maxn];
	unordered_map<LL, int> idx;
	int getIndex(LL value, int length) {
		unordered_map<LL, int>::iterator it = idx.find(value);
		if(it != idx.end())
			return it -> second;
		len[tot] = length;
		return idx[value] = tot++;
	}
public:
	int tot, len[maxn];
	void init() {
		pw1[0] = pw2[0] = 1;
		for(int i = 1; i < maxn; ++i) {
			pw1[i] = (LL)pw1[i - 1] * seed % mod1;
			pw2[i] = (LL)pw2[i - 1] * seed % mod2;
		}
	}
	void parse(int len, char buf[]) {
		tot = 0;
		unordered_map<LL, int>().swap(idx);
		idx.reserve(len);
		int ph1 = hh1[0] = 0, ph2 = hh2[0] = 0;
		for(int i = 0; i < len; ++i) {
			int ch = buf[i] - 'a' + 1;
			hh1[i + 1] = ph1 = ((LL)ph1 * seed + ch) % mod1;
			hh2[i + 1] = ph2 = ((LL)ph2 * seed + ch) % mod2;
		}
	}
	int query(int L, int R) { // [L, R)
		int ph1 = (hh1[R] - (LL)pw1[R - L] * hh1[L]) % mod1;
		int ph2 = (hh2[R] - (LL)pw2[R - L] * hh2[L]) % mod2;
		return getIndex((LL)(ph1 < 0 ? ph1 + mod1 : ph1) << 32 | (ph2 < 0 ? ph2 + mod2 : ph2), R - L);
	}
} ht;
int ptot, sz[maxn], lnk[maxn], dsu[maxn], val[maxn];
struct List {
	int nxt, v;
} p[maxn << 1 | 1];
inline int addPoints(int u, int v) {
	if(sz[u] && p[lnk[u]].v == v)
		return sz[u] - 1;
	p[ptot] = (List){lnk[u], v};
	lnk[u] = ptot++;
	return sz[u]++;
}
int etot, ord[maxn << 3 | 1], *ord2 = ord + (maxn << 2 | 1);
struct Event {
	int idx, L, R, v;
} eve[maxn << 2 | 1];
void rebuild() {
	memset(ctr, 0, n * sizeof(int));
	for(int i = 0; i < etot; ++i) {
		++ctr[eve[i].L];
		++ctr[eve[i].R];
	}
	for(int i = 1; i < n; ++i)
		ctr[i] += ctr[i - 1];
	for(int i = 0; i < etot; ++i) {
		ord[--ctr[eve[i].L]] = i << 1;
		ord[--ctr[eve[i].R]] = i << 1 | 1;
	}
	ptot = 0;
	memset(sz, 0, ht.tot * sizeof(int));
	memset(lnk, -1, ht.tot * sizeof(int));
	for(int i = 0; i < ht.tot; ++i)
		addPoints(i, 0);
	for(int i = 0; i < etot << 1; ++i) {
		int o = ord[i] >> 1, &x = ord[i] & 1 ? eve[o].R : eve[o].L;
		x = addPoints(eve[o].idx, x);
	}
	for(int i = 0; i < ht.tot; ++i)
		addPoints(i, ht.len[i]);
	memset(ctr, 0, n * sizeof(int));
	for(int i = 0; i < etot; ++i)
		++ctr[eve[i].v];
	for(int i = 1; i < n; ++i)
		ctr[i] += ctr[i - 1];
	for(int i = 0; i < etot; ++i)
		ord2[--ctr[eve[i].v]] = i;
	memset(ctr, 0, ht.tot * sizeof(int));
	for(int i = 0; i < etot; ++i)
		++ctr[eve[i].idx];
	for(int i = 1; i < ht.tot; ++i)
		ctr[i] += ctr[i - 1];
	for(int i = 0; i < etot; ++i)
		ord[--ctr[eve[ord2[i]].idx]] = ord2[i];
}
inline int cmpF(int pL, int pR, int qL, int qR) { // [pL, pR), [qL, qR)
	int adt = min(lcp(pL, qL), min(pR - pL, qR - qL));
	int pCh = (pL += adt) < pR ? buf[pL] : -1;
	int qCh = (qL += adt) < qR ? buf[qL] : -1;
	return (pCh > qCh) - (pCh < qCh);
}
inline int cmpB(int pL, int pR, int qL, int qR) { // [pL, pR), [qL, qR)
	int adt = min(lcp(pL, qL), min(pR - pL, qR - qL));
	int pCh = (pL += adt) < pR ? buf[pL] : 256;
	int qCh = (qL += adt) < qR ? buf[qL] : 256;
	return (pCh < qCh) - (pCh > qCh);
}
void getRuns(int (*cmp)(int, int, int, int)) {
	static int stot, stk[maxn];
	stk[stot = 0] = n;
	for(int i = n - 1; i >= 0; --i) {
		for( ; stot && cmp(i, stk[stot], stk[stot], stk[stot - 1]) < 0; --stot);
		int L = i - lcs(i - 1, stk[stot] - 1);
		int R = stk[stot] + lcp(i, stk[stot]);
		int plen = R - L, per = stk[stot] - i;
		if(per + per <= plen && L < i && i <= L + per) {
			int ctr = plen / per, rem = plen % per;
			int pos = lsr(L, L + per), sft = pos - L;
			int idx = ht.query(pos, pos + per);
			if(ctr > 1) { // always true
				int vL = per - sft, vR = rem - sft + 1;
				vL >= per && (vL -= per);
				vR <= 0 && (vR += per);
				eve[etot++] = (Event){idx, vL, vR, ctr - 1};
			}
			if(ctr > 2 && rem + 1 < per) {
				int vL = rem - sft + 1, vR = per - sft;
				vL < 0 && (vL += per);
				eve[etot++] = (Event){idx, vL, vR, ctr - 2};
			}
		}
		stk[++stot] = i;
	}
}
int main() {
	Log[0] = -1;
	for(int i = 1; i < maxn; ++i)
		Log[i] = Log[i >> 1] + 1;
	ht.init();
	scanf("%d", &t);
	while(t--) {
		scanf("%s", buf);
		n = strlen(buf);
		reverse(buf, buf + n);
		suf.init(n, buf);
		memcpy(rk2, suf.rk, n * sizeof(int));
		reverse(rk2, rk2 + n);
		st2.init(n, suf.ht);
		reverse(buf, buf + n);
		suf.init(n, buf);
		st.init(n, suf.ht);
		sp.init(n, suf.rk);
		LL ans = n * (n + 1LL) / 2;
		for(int i = 0; i < n; ++i)
			ans -= suf.ht[i];
		etot = 0;
		ht.parse(n, buf);
		getRuns(cmpF);
		getRuns(cmpB);
		rebuild();
		ord[etot] = etot;
		eve[etot].idx = -1;
		for(int i = 0; i < etot; ) {
			int idx = eve[ord[i]].idx;
			static int dsu[maxn], val[maxn];
			memset(dsu, -1, sz[idx] * sizeof(int));
			memset(val, 0, sz[idx] * sizeof(int));
			function<int(int)> dsuFind;
			dsuFind = [&](int x) {
				return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
			};
			auto cover = [&](int L, int R, int v) {
				for(int j = dsuFind(L); j < R; j = dsuFind(j)) {
					val[j] = v;
					dsu[j] = j + 1;
				}
			};
			for( ; idx == eve[ord[i]].idx; ++i) {
				int o = ord[i];
				if(eve[o].L < eve[o].R) {
					cover(eve[o].L, eve[o].R, eve[o].v);
				} else {
					cover(eve[o].L, sz[idx] - 1, eve[o].v);
					cover(0, eve[o].R, eve[o].v);
				}
			}
			for(int j = sz[idx] - 2, it = lnk[idx], jt = p[it].nxt; j >= 0; --j, it = jt, jt = p[jt].nxt)
				if(val[j])
					ans -= (LL)val[j] * (p[it].v - p[jt].v);
		}
		printf("%lld\n", ans);
	}
	return 0;
}