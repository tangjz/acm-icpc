#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, a[maxn], s[maxn], b[maxn], dsu[maxn], ans[maxn], cur;
set<int> sp[maxn], lft[maxn], rht[maxn];
inline int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void set_merge(set<int> &src, set<int> &dst) {
	if(src.size() > dst.size())
		src.swap(dst);
	for(set<int>::iterator it = src.begin(); it != src.end(); ++it)
		dst.insert(*it);
	set<int>().swap(src);
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(sp[u].size() < sp[v].size()) {
		for(set<int>::iterator it = sp[u].begin(); it != sp[u].end(); ++it) {
			int val = s[*it - 1] + m;
			set<int>::iterator jt = rht[v].lower_bound(val);
			if(jt != rht[v].end())
				cur = min(cur, *jt - val);
			if(jt != rht[v].begin())
				cur = min(cur, val - *(--jt));
		}
	} else {
		for(set<int>::iterator it = sp[v].begin(); it != sp[v].end(); ++it) {
			int val = s[*it] - m;
			set<int>::iterator jt = lft[u].lower_bound(val);
			if(jt != lft[u].end())
				cur = min(cur, *jt - val);
			if(jt != lft[u].begin())
				cur = min(cur, val - *(--jt));
		}
	}
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	set_merge(sp[u], sp[v]); 
	set_merge(lft[u], lft[v]); 
	set_merge(rht[u], rht[v]); 
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			s[i] = s[i - 1] + a[i];
			dsu[i] = -1;
		}
		for(int i = 1; i <= n; ++i)
			scanf("%d", b + i);
		cur = ~0u >> 1;
		for(int i = n; i >= 1; --i) {
			int u = b[i];
			sp[u].insert(u);
			lft[u].insert(s[u - 1]);
			rht[u].insert(s[u]);
			cur = min(cur, abs(a[u] - m));
			if(u > 1 && sp[dsu_find(u - 1)].size() > 0)
				dsu_merge(u - 1, u);
			if(u < n && sp[dsu_find(u + 1)].size() > 0)
				dsu_merge(u, u + 1);
			ans[i] = cur;
		}
		for(int i = 1; i <= n; ++i) {
			printf("%d\n", ans[i]);
			set<int>().swap(sp[i]);
			set<int>().swap(lft[i]);
			set<int>().swap(rht[i]);
		}
	}
	return 0;
}
