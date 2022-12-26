#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxm = (int)3e4 + 1;
int n, a[maxn], ord[maxn], tot, in[maxn], out[maxn], bit[2][maxn];
vector<int> e[maxn];
void dfs(int u, int fa) {
	in[u] = ++tot;
	for(int v : e[u]) {
		if(v == fa)
			continue;
		dfs(v, u);
	}
	out[u] = tot;
}
void bit_upd(int bit[maxn], int x, int v) {
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int bit_que(int bit[maxn], int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		ord[i] = i;
	}
	sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
		return a[u] < a[v];
	});
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, -1);
	bitset<maxm> msk;
	msk.set(0);
	for(int i = 1; i <= n; ++i) {
		int o = ord[i];
		int v0 = bit_que(bit[0], in[o]);
		int v1 = bit_que(bit[1], out[o]) - bit_que(bit[1], in[o] - 1);
		msk = msk << v0 | msk << v1;
		bit_upd(bit[0], in[o] + 1, 1);
		bit_upd(bit[0], out[o] + 1, -1);
		bit_upd(bit[1], in[o], 1);
	}
	scanf("%d", &n);
	while(n--) {
		int k;
		scanf("%d", &k);
		puts(msk.test(k) ? "Orz" : "QAQ");
	}
	return 0;
}