#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 3, INF = 0x3f3f3f3f;
int n, dt, a[maxn], b[maxn], c[maxn], s[maxn], pL[maxn], pR[maxn];
priority_queue<pair<int, int> > Q;
inline void erase(int x) {
	pL[pR[x]] = pL[x];
	pR[pL[x]] = pR[x];
}
int main() {
	scanf("%d%d", &n, &dt);
	pR[0] = 1;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		s[i] = b[i] = a[i];
		c[i] = 1;
		pL[i] = i - 1;
		pR[i] = i + 1;
		Q.push(make_pair(-b[i], i));
	}
	pL[n + 1] = n;
	b[0] = b[n + 1] = INF;
	while(!Q.empty()) {
		int u = Q.top().second, lft = pL[u], rht = pR[u];
		Q.pop();
		if(pR[lft] != u || pL[rht] != u || b[lft] < b[u] || b[rht] < b[u])
			continue;
		int cnt = 0, upp = INF;
		if(b[lft] < INF) {
			++cnt;
			upp = min(upp, b[lft]);
		}
		if(b[rht] < INF) {
			++cnt;
			upp = min(upp, b[rht]);
		}
		upp = min(upp, ((cnt * dt + s[u] * 2) / c[u] + 1) / 2);
		if(upp < b[u])
			continue;
		b[u] = upp;
		cnt = 0;
		if(b[lft] == b[u]) {
			erase(u);
			c[lft] += c[u];
			s[lft] += s[u];
			u = lft;
			++cnt;
		}
		if(b[u] == b[rht]) {
			erase(rht);
			c[u] += c[rht];
			s[u] += s[rht];
			++cnt;
		}
		if(cnt)
			Q.push(make_pair(-b[u], u));
	}
	for(int i = 1; i <= n; ) {
		for(int j = c[i], v = b[i]; j > 0; --j)
			b[i++] = v;
	}
	long long ans = (b[1] - a[1]) * (b[1] - a[1]);
	for(int i = 2; i <= n; ++i)
		ans += dt * abs(b[i] - b[i - 1]) + (b[i] - a[i]) * (b[i] - a[i]);
	printf("%lld\n", ans);
	return 0;
}