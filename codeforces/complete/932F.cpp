#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, LL> Point;
const int maxn = (int)1e5 + 1;
const LL INF = (LL)1e15 + 1;
int n, a[maxn], b[maxn], fa[maxn];
LL f[maxn];
vector<int> e[maxn];
set<Point> s[maxn];
inline double area(Point A, Point B, Point C) {
	int x1 = B.first - A.first, x2 = C.first - B.first;
	LL y1 = B.second - A.second, y2 = C.second - B.second;
	return (double)x1 * y2 - (double)x2 * y1; // 1e20
}
void insert(set<Point> &sp, Point p) {
	set<Point>::iterator it = sp.lower_bound(p), jt = it == sp.begin() ? it : it--; // (*it, *jt]
	if(jt != sp.end() && jt != sp.begin() && area(*it, p, *jt) <= 0)
		return;
	if(jt != sp.begin())
		while(it != sp.begin()) {
			jt = it--;
			if(area(*it, *jt, p) <= 0)
				sp.erase(*jt);
		}
	jt = sp.lower_bound(p);
	it = jt == sp.end() ? jt : jt++;
	if(it != sp.end())
		while(jt != sp.end()) {
			if(area(p, *it, *jt) <= 0)
				sp.erase(*it);
			it = jt++;
		}
	sp.insert(p);
}
LL query(set<Point> &sp, Point p) { // min prod
	if(!sp.size())
		return 0;
	int L = sp.begin() -> first, R = sp.rbegin() -> first;
	while(L < R) {
		int M = (L + R + 1) >> 1;
		set<Point>::iterator it = sp.lower_bound((Point){M, -INF}), jt = it--;
		if((LL)(jt -> first - it -> first) * p.first + (jt -> second - it -> second) * p.second <= 0) // 1e15
			L = M;
		else
			R = M - 1;
	}
	Point q = *sp.lower_bound((Point){L, -INF});
	return (LL)p.first * q.first + p.second * q.second; // 1e15
}
void dfs(int u) {
	for(auto &v : e[u])
		if(v != fa[u]) {
			fa[v] = u;
			dfs(v);
			if(s[u].size() < s[v].size())
				s[u].swap(s[v]);
			for(auto &p : s[v])
				insert(s[u], p);
			set<Point>().swap(s[v]);
		}
	f[u] = query(s[u], (Point){a[u], 1LL});
	insert(s[u], (Point){b[u], f[u]});
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", b + i);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1);
	for(int i = 1; i <= n; ++i)
		printf("%lld%c", f[i], " \n"[i == n]);
	return 0;
}
