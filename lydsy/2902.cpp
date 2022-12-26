#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1.5e5 + 1, maxs = (int)3e5 + 1;
int n, m, dt, a[maxn];
pair<int, int> op[maxn];
int tot, sq, que[maxs], nxt[maxs], upp[maxs], cnt[maxs];
pair<int, int> jmp[maxs];
inline void upd(int x, int v) {
	int las = cnt[x];
	cnt[x] += v;
	if(!las == !cnt[x])
		return;
	for(int i = x, rem = x % sq; rem >= 0; --i, --rem) {
		int j = cnt[i] ? nxt[i] : i + 1, k = !!cnt[i];
		jmp[i] = j < upp[i] ? make_pair(jmp[j].first, jmp[j].second + k) : make_pair(j, k);
	}
}
int main() {
	scanf("%d%d%d", &n, &dt, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		que[tot++] = a[i];
	}
	for(int i = 0; i < m; ++i) {
		int &id = op[i].first, &pos = op[i].second;
		scanf("%d%d", &id, &pos);
		que[tot++] = pos;
	}
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(sq = 1; sq * sq < tot; ++sq);
	que[tot] = que[tot - 1] + dt;
	for(int i = 0; i < n; ++i) {
		a[i] = lower_bound(que, que + tot, a[i]) - que;
		++cnt[a[i]];
	}
	nxt[tot] = tot;
	for(int i = tot - 1; i >= 0; --i) {
		for(nxt[i] = nxt[i + 1]; que[nxt[i] - 1] - que[i] > dt; --nxt[i]);
		upp[i] = min(tot, (i / sq + 1) * sq);
		int j = cnt[i] ? nxt[i] : i + 1, k = !!cnt[i];
		jmp[i] = j < upp[i] ? make_pair(jmp[j].first, jmp[j].second + k) : make_pair(j, k);
	}
	for(int i = 0; i < m; ++i) {
		int u = op[i].first, v = op[i].second;
		upd(a[u], -1);
		upd(a[u] = lower_bound(que, que + tot, v) - que, 1);
		for(u = v = 0; u < tot; v += jmp[u].second, u = jmp[u].first);
		printf("%d\n", v);
	}
	return 0;
}
