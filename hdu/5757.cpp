#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
struct Node {
	LL sum;
	int aRem, aPos, aUpp;
	int bRem, bPos, bUpp;
	bool operator < (Node const &t) const {
		return sum < t.sum;
	}
};
LL solve(int tot, int m, int aLen, int a[], int bLen, int b[], bool neg) {
	if(neg) {
		for(int i = 0; i < aLen; ++i)
			a[i] = -a[i];
		for(int i = 0; i < bLen; ++i)
			b[i] = -b[i];
	}
	sort(a, a + aLen, greater<int>());
	sort(b, b + bLen, greater<int>());
	LL tmp = 0;
	for(int i = 0; i < bLen && i < tot; ++i)
		tmp += b[i];
	priority_queue<Node> Q;
	for(int i = 0, j = tot; i <= aLen && j >= 0; ++i, --j) {
		if(j <= bLen && (j & 1) == neg)
			Q.push((Node){tmp, i - 1, i - 1, aLen - 1, j - 1, j - 1, bLen - 1});
		if(i < aLen)
			tmp += a[i];
		if(j && j <= bLen)
			tmp -= b[j - 1];
	}
	for(int i = 1; i < m; ++i) {
		Node cur = Q.top(), nxt;
		Q.pop();
		if(cur.aRem >= 0) {
			if(cur.aPos < cur.aUpp) {
				nxt = cur;
				nxt.sum += a[nxt.aPos + 1] - a[nxt.aPos];
				++nxt.aPos;
				Q.push(nxt);
			}
			if(cur.aRem > 0 && cur.aRem < cur.aPos) {
				nxt = cur;
				nxt.sum += a[nxt.aRem] - a[nxt.aRem - 1];
				nxt.aUpp = nxt.aPos - 1;
				nxt.aPos = nxt.aRem--;
				Q.push(nxt);
			}
		}
		if(cur.bRem >= 0) {
			if(cur.bPos < cur.bUpp) {
				nxt = cur;
				nxt.aRem = -1;
				nxt.sum += b[nxt.bPos + 1] - b[nxt.bPos];
				++nxt.bPos;
				Q.push(nxt);
			}
			if(cur.bRem > 0 && cur.bRem < cur.bPos) {
				nxt = cur;
				nxt.aRem = -1;
				nxt.sum += b[nxt.bRem] - b[nxt.bRem - 1];
				nxt.bUpp = nxt.bPos - 1;
				nxt.bPos = nxt.bRem--;
				Q.push(nxt);
			}
		}
	}
	return (neg ? -1 : 1) * Q.top().sum;
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
	while(scanf("%d%d%d", &n, &m, &k) == 3 && !(!n && !m && !k)) {
		int cntP = 0, cntZ = 0, cntN = 0;
		static int pos[maxn], neg[maxn];
		for(int i = 0; i < n; ++i) {
			char typ[3];
			scanf("%s", typ);
			if(typ[0] == '+') {
				scanf("%d", pos + (cntP++));
			} else if(typ[0] == '-') {
				scanf("%d", neg + (cntN++));
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
			printf("+ %lld\n", solve(m, k, cntP, pos, cntN, neg, 0));
			continue;
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
			printf("- %lld\n", solve(m, k - sum, cntP, pos, cntN, neg, 1));
		}
	}
	return 0;
}
