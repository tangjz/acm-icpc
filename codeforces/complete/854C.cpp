#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = (int)3e5 + 9, mod = (int)1e9 + 7;
int n, m, c[maxn], out[maxn];
LL ans;
set<pair<int, int> > sp;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", c + i);
	for(int i = 1; i <= m; ++i)
		sp.insert(make_pair(c[i], i));
	for(int i = 1; i <= n; ++i) {
		if(i + m <= n)
			sp.insert(make_pair(c[i + m], i + m));
		pair<int, int> cur = *sp.rbegin();
		sp.erase(cur);
		out[cur.second] = i + m;
		ans += (LL)(i + m - cur.second) * cur.first;
	}
	printf("%I64d\n", ans);
	for(int i = 1; i <= n; ++i)
		printf("%d%c", out[i], " \n"[i == n]);
	return 0;
}
