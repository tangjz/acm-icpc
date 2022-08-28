#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef priority_queue<LL, vector<LL>, greater<LL> > Heap;
const int maxn = (int)1e5 + 1;
int n, cap[maxn], rem[maxn];
vector<pair<int, int> > e[maxn];
LL tag[2][maxn];
Heap que[2][maxn];
void merge(LL &tagU, Heap &queU, LL &tagV, Heap &queV) {
	if(queU.size() < queV.size()) {
		swap(tagU, tagV);
		queU.swap(queV);
	}
	while(!queV.empty()) {
		queU.push(queV.top() + tagV - tagU);
		queV.pop();
	}
}
LL dfs(int u, int fa) {
	LL ret = 0;
	rem[u] = max(-cap[u], 0);
	tag[0][u] = tag[1][u] = 0;
	Heap().swap(que[0][u]);
	Heap().swap(que[1][u]);
	for(int i = 0; i < cap[u]; ++i)
		que[0][u].push(0LL);
	for(auto it : e[u]) {
		int v = it.first;
		int w = it.second;
		if(v == fa)
			continue;
		ret += dfs(v, u) + (LL)rem[v] * w;
		rem[u] += rem[v];
		merge(tag[0][u], que[0][u], tag[0][v] += w, que[0][v]);
		merge(tag[1][u], que[1][u], tag[1][v] += w, que[1][v]);
	}
	while(rem[u] && !que[0][u].empty()) {
		LL cost = que[0][u].top() + tag[0][u];
		que[0][u].pop();
		que[1][u].push(-cost - tag[1][u]);
		--rem[u];
		ret += cost;
	}
	LL cost0, cost1;
	while(!que[0][u].empty() && !que[1][u].empty() && (cost0 = que[0][u].top() + tag[0][u]) + (cost1 = que[1][u].top() + tag[1][u]) < 0) {
		ret += cost0 + cost1;
		que[0][u].pop();
		que[1][u].pop();
		que[0][u].push(-cost1 - tag[0][u]);
		que[1][u].push(-cost0 - tag[1][u]);
	}
	return ret;
}
int main() {
	int m;
    scanf("%d%d", &n, &m);
    for(int i = 2; i <= n; ++i)
        e[i >> 1].push_back({i, 1});
	for(int i = 1; i <= n; ++i)
        scanf("%d", cap + i);
    while(m--) {
        int x;
        scanf("%d", &x);
        --cap[x];
    }
	printf("%lld\n", dfs(1, -1));
	return 0;
}
