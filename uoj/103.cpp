#include <bits/stdc++.h>
using namespace std;
namespace PalindromeTree {
	const int maxn = (int)3e5 + 3, maxc = 26;
	int n, tot, last, len[maxn], fail[maxn], nxt[maxn][maxc], cnt[maxn];
	char buf[maxn];
	int newNode(int length, int prev = 0) {
		assert(tot + 1 < maxn);
		len[tot] = length;
		fail[tot] = prev;
		memset(nxt[tot], 0, sizeof nxt[0]);
		return tot++;
	}
	void init() {
		n = tot = 0;
		last = newNode(0);
		int tp = newNode(-1, last);
		fail[last] = tp;
		buf[0] = '\0';
	}
	void append(char ch) {
		int o = (buf[++n] = ch) - 'a';
		for( ; buf[n - len[last] - 1] != buf[n]; last = fail[last]);
		if(!nxt[last][o]) {
			int p = newNode(len[last] + 2);
			int q = fail[last];
			for( ; buf[n - len[q] - 1] != buf[n]; q = fail[q]);
			fail[p] = nxt[q][o];
			nxt[last][o] = p;
		}
		last = nxt[last][o];
		++cnt[last];
	}
	typedef long long LL;
	void solve() {
		static char str[maxn];
		scanf("%s", str);
		init();
		for(int i = 0; str[i]; ++i)
			append(str[i]);
		LL ans = 0;
		for(int i = tot; i; --i) {
			cnt[fail[i]] += cnt[i];
			ans = max(ans, (LL)len[i] * cnt[i]);
		}
		printf("%lld\n", ans);
	}
}
int main() {
	PalindromeTree::solve();
	return 0;
}
