#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e4 + 1, BLEN = 12, maxl = 7;
const LL BASE = (LL)1e12;
struct BigInt {
	int sgn, len;
	LL num[maxl];
	bool operator < (BigInt const &t) const {
		if(sgn != t.sgn)
			return sgn < t.sgn;
		if(len != t.len)
			return sgn * (len - t.len) < 0;
		for(int i = len - 1; i >= 0; --i)
			if(num[i] != t.num[i])
				return sgn * (num[i] - t.num[i]) < 0;
		return 0;
	}
	void println() const {
		if(sgn < 0)
			putchar('-');
		printf("%lld", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%0*lld", BLEN, num[i]);
		putchar('\n');
	}
	void operator *= (int const &t) {
		LL rem = 0;
		for(int i = 0; i < len; ++i) {
			rem += num[i] * t;
			num[i] = rem % BASE;
			rem /= BASE;
		}
		if(rem)
			num[len++] = rem;
		assert(len <= maxl);
	}
	void operator /= (int const &t) {
		LL rem = 0;
		for(int i = len - 1; i >= 0; --i) {
			rem = rem * BASE + num[i];
			num[i] = rem / t;
			rem %= t;
		}
		assert(rem == 0);
		if(len > 1 && !num[len - 1])
			--len;
	}
};
struct Node {
	BigInt prd;
	int aRem, aPos, aUpp;
	int bRem, bPos, bUpp;
	bool operator < (Node const &t) const {
		return prd < t.prd;
	}
};
void solve(int tot, int m, int aLen, int a[], int bLen, int b[], bool neg) {
	if(neg) {
		sort(a, a + aLen);
		sort(b, b + bLen);
	} else {
		sort(a, a + aLen, greater<int>());
		sort(b, b + bLen, greater<int>());
	}
	BigInt tmp = {};
	tmp.sgn = neg ? -1 : 1;
	tmp.len = tmp.num[0] = 1;
	for(int i = 0; i < bLen && i < tot; ++i)
		tmp *= b[i];
	priority_queue<Node> Q;
	for(int i = 0, j = tot; i <= aLen && j >= 0; ++i, --j) {
		if(j <= bLen && (j & 1) == neg)
			Q.push((Node){tmp, i - 1, i - 1, aLen - 1, j - 1, j - 1, bLen - 1});
		if(j && j <= bLen)
			tmp /= b[j - 1];
		if(i < aLen)
			tmp *= a[i];
	}
	for(int i = 1; i < m; ++i) {
		Node cur = Q.top(), nxt;
		Q.pop();
		if(cur.aRem >= 0) {
			if(cur.aPos < cur.aUpp) {
				nxt = cur;
				nxt.prd /= a[nxt.aPos];
				nxt.prd *= a[nxt.aPos + 1];
				++nxt.aPos;
				Q.push(nxt);
			}
			if(cur.aRem > 0 && cur.aRem < cur.aPos) {
				nxt = cur;
				nxt.prd /= a[nxt.aRem - 1];
				nxt.prd *= a[nxt.aRem];
				nxt.aUpp = nxt.aPos - 1;
				nxt.aPos = nxt.aRem--;
				Q.push(nxt);
			}
		}
		if(cur.bRem >= 0) {
			if(cur.bPos < cur.bUpp) {
				nxt = cur;
				nxt.aRem = -1;
				nxt.prd /= b[nxt.bPos];
				nxt.prd *= b[nxt.bPos + 1];
				++nxt.bPos;
				Q.push(nxt);
			}
			if(cur.bRem > 0 && cur.bRem < cur.bPos) {
				nxt = cur;
				nxt.aRem = -1;
				nxt.prd /= b[nxt.bRem - 1];
				nxt.prd *= b[nxt.bRem];
				nxt.bUpp = nxt.bPos - 1;
				nxt.bPos = nxt.bRem--;
				Q.push(nxt);
			}
		}
	}
	Q.top().prd.println();
}
inline void getBinom(int n, int upp, int bin[]) {
	bin[0] = 1;
	for(int i = 1; i <= n - i; ++i)
		if(bin[i - 1] > upp) {
			bin[i] = bin[i - 1];
		} else {
			LL tmp = bin[i - 1] * (n - i + 1LL) / i;
			bin[i] = tmp > upp ? upp + 1 : tmp;
		}
	for(int i = n; i > n - i; --i)
		bin[i] = bin[n - i];
}
int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	int cntP = 0, cntZ = 0, cntN = 0;
	static int pos[maxn], neg[maxn];
	for(int i = 0, x; i < n; ++i) {
		scanf("%d", &x);
		if(x > 0) {
			pos[cntP++] = x;
		} else if(x < 0) {
			neg[cntN++] = -x;
		} else {
			++cntZ;
		}
	}
	int sum = 0;
	static int f[maxn], g[maxn];
	if(cntZ < n) {
		getBinom(cntP, k - 1, f);
		getBinom(cntN, k - 1, g);
		for(int i = m & 1, j = m - i; i <= cntP && j >= 0 && sum < k; i += 2, j -= 2)
			if(j <= cntN && f[i] && g[j]) {
				LL nxt = sum + (LL)f[i] * g[j];
				sum = nxt < k ? nxt : k;
			}
	}
	if(sum >= k) {
		solve(m, k, cntP, pos, cntN, neg, 0);
		return 0;
	}
	k -= sum;
	sum = 0;
	if(cntZ > 0) {
		getBinom(cntZ, k - 1, f);
		getBinom(n - cntZ, k - 1, g);
		for(int i = 1, j = m - i; i <= cntZ && j >= 0 && sum < k; ++i, --j)
			if(j <= n - cntZ && f[i] && g[j]) {
				LL nxt = sum + (LL)f[i] * g[j];
				sum = nxt < k ? nxt : k;
			}
	}
	if(sum >= k) {
		puts("0");
	} else {
		solve(m, k - sum, cntP, pos, cntN, neg, 1);
	}
	return 0;
}