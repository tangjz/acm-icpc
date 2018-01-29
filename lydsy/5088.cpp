#include <bits/stdc++.h>
typedef long long LL;
typedef std::pair<LL, int> Node;
const int maxn = (int)1e5 + 1, maxq = (int)1e6 + 1;
void solve(int n, int a[], int m, LL b[]) {
	std::priority_queue<Node> Q;
	for(int i = 1; i <= n; ++i)
		Q.push(std::make_pair(0LL - a[i], i));
	for(int i = 1; i <= m; ++i) {
		Node tmp = Q.top();
		Q.pop();
		b[i] = -tmp.first;
		Q.push(std::make_pair(tmp.first - a[tmp.second], tmp.second));
	}
}
int t, n, m, q, w[maxn];
LL a[maxq], b[maxq], ans;
int main() {
	scanf("%d%d%d", &q, &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", w + i);
	solve(n, w, q, a);
	for(int i = 1; i <= m; ++i)
		scanf("%d", w + i);
	solve(m, w, q, b);
	ans = 0;
	for(int i = 1; i <= q; ++i)
		ans = std::max(ans, a[i] + b[q - i + 1]);
	printf("%lld\n", ans);
	return 0;
}
