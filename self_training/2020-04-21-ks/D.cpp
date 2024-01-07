#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e6 + 1, maxc = 26 + 1;
namespace Trie {
	int tot, rt, ctr[maxn], nxt[maxn][maxc];
	int newNode() {
		ctr[tot] = 0;
		memset(nxt[tot], 0, sizeof nxt[0]);
		return tot++;
	}
	void init() {
		tot = 0;
		rt = newNode();
	}
	void parse() {
		static char buf[maxn];
		scanf("%s", buf);
		int pos = rt;
		for(int i = 0; buf[i]; ++i) {
			int ch = buf[i] - 'A';
			if(!nxt[pos][ch])
				nxt[pos][ch] = newNode();
			pos = nxt[pos][ch];
		}
		++ctr[pos];
	}
	int dfs(int dep, int u, int K, int &ans) {
		int cnt = ctr[u];
		for(int i = 0; i < maxc; ++i)
			if(nxt[u][i])
				cnt += dfs(dep + 1, nxt[u][i], K, ans);
		if(cnt >= K) {
			ans += cnt / K * dep;
			cnt %= K;
		}
		return cnt;
	}
}
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int N, K;
		scanf("%d%d", &N, &K);
		Trie::init();
		for(int i = 0; i < N; ++i)
			Trie::parse();
		int ans = 0;
		Trie::dfs(0, Trie::rt, K, ans);
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}