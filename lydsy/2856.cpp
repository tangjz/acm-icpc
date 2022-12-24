#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
int n, m, ord[maxn], ans[maxn];
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
	bool operator == (Point const &t) const {
		return x == t.x && y == t.y;
	}
	bool operator < (Point const &t) const {
		LL tmp = det(t);
		return tmp > 0 || (!tmp && x < t.x);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
} p[maxn];
struct Line {
	Point u, v;
	bool operator < (Line const &t) const {
		LL tmp = u.det(t.u);
		return tmp < 0 ? ((t.v - t.u).det(u - t.u) > 0) : ((v - u).det(t.u - u) < 0);
	}
};
set<Line> sp;
bool cmp(int const &u, int const &v) {
	return p[u] < p[v];
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		p[i].read();
		ord[i] = i;
	}
	if(n == 2 && !p[0].det(p[1])) {
		if(p[1] < p[0])
			swap(ord[0], ord[1]);
		--n;
	}
	if(n <= 2) {
		printf("%d\n", n);
		for(int i = 0; i < n; ++i)
			printf("%d%c", ord[i] + 1, " \n"[i == n - 1]);
		return 0;
	}
	int pos = 0;
	for(int i = 1; i < n; ++i)
		if(p[i] < p[pos])
			pos = i;
	rotate(ord, ord + pos, ord + n);
	bool rev = 0;
	if((p[ord[1]] - p[ord[0]]).det(p[ord[n - 1]] - p[ord[0]]) > 0) {
		rev = 1;
		reverse(ord + 1, ord + n);
	}
	pos = 1;
	for(int i = 2; i < n; ++i) {
		LL tmp = p[ord[pos]].det(p[ord[i]]);
		if(tmp > 0 || (!tmp && p[ord[pos]].x > p[ord[i]].x))
			pos = i;
	}
	sort(ord, ord + pos + 1, cmp);
	for(int i = 0; i <= pos; ++i) {
		int u = ord[i], pu = u ? u - 1 : n - 1, su = u + 1 < n ? u + 1 : 0;
		if(rev)
			swap(pu, su);
		bool chk = 0;
		if(sp.size() && sp.begin() -> v == p[u])
			chk = 1;
		if(p[pu].det(p[u]) > 0)
			sp.erase((Line){p[pu], p[u]});
		if(p[u].det(p[su]) > 0) {
			sp.insert((Line){p[u], p[su]});
			if(sp.begin() -> u == p[u]) {
				assert(sp.begin() -> v == p[su]);
				chk = 1;
			}
		}
		if(chk)
			ans[m++] = u;
	}
	sort(ans, ans + m);
	printf("%d\n", m);
	for(int i = 0; i < m; ++i)
		printf("%d%c", ans[i] + 1, " \n"[i == m - 1]);
	return 0;
}
