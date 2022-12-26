#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e4 + 1;
const double eps = 1e-9;
inline int sgn(double x) {
	return (x > eps) - (x < -eps);
}
struct Circle {
	int x, y, r;
	void read() {
		scanf("%d%d%d", &x, &y, &r);
	}
	double getY(int pX, bool up) {
		int dX = x - pX;
		double dY = sqrtl(r * r - dX * dX);
		return up ? y + dY : y - dY;
	}
};
struct Curve {
	static int pX;
	Circle *c;
	bool up;
	bool operator == (Curve const &t) const {
		return c == t.c && up == t.up;
	}
	bool operator < (Curve const &t) const {
		double dif = (c -> getY(pX, up)) - (t.c -> getY(pX, t.up));
		return sgn(dif) < 0 || (!sgn(dif) && up < t.up);
	}
};
int Curve::pX;
struct Event {
	int typ, pX;
	Circle *c;
	bool operator < (Event const &t) const {
		return pX < t.pX || (pX == t.pX && typ > t.typ);
	}
};

void solve() {
	int n;
	scanf("%d", &n);
	set<Curve> sp;
	vector<Circle> a(n);
	vector<Event> eve(n + n);
	vector<int> par(n, -1);
	vector<vector<int> > e(n);
	for(int i = 0; i < n; ++i) {
		Circle &cur = a[i];
		cur.read();
		eve[i << 1] = {1, cur.x - cur.r, &cur};
		eve[i << 1 | 1] = {-1, cur.x + cur.r, &cur};
	}
	sort(eve.begin(), eve.end());
	for(auto &it: eve) {
		int u = it.c - &a[0];
		Curve::pX = it.pX;
		if(it.typ == 1) {
			auto jt = sp.insert((Curve){it.c, false}).first;
			auto kt = sp.insert((Curve){it.c, true}).first;
			if(jt != sp.begin() && (++kt) != sp.end()) {
				--jt;
				if(jt -> up == kt -> up) {
					par[u] = (jt -> up ? kt -> c : jt -> c) - &a[0];
				} else if(!(jt -> up) && (kt -> up)) {
					assert(jt -> c == kt -> c);
					par[u] = (jt -> c) - &a[0];
				} else {
					par[u] = par[(jt -> c) - &a[0]];
					assert(par[(kt -> c) - &a[0]] == par[u]);
				}
			}
			if(par[u] != -1)
				e[par[u]].push_back(u);
		} else {
			sp.erase((Curve){it.c, false});
			sp.erase((Curve){it.c, true});
		}
	}
	int ans = 0;
	vector<int> ord(n), sg(n);
	for(int i = 0; i < n; ++i) {
		if(par[i] != -1)
			continue;
		int tot = 0;
		ord[tot++] = i;
		for(int j = 0; j < tot; ++j) {
			int u = ord[j];
			for(int v: e[u])
				ord[tot++] = v;
		}
		for(int j = tot - 1; j >= 0; --j) {
			int u = ord[j];
			if(par[u] != -1)
				sg[par[u]] ^= sg[u] + 1;
		}
		ans ^= sg[i] + 1;
	}
	puts(ans ? "Alice" : "Bob");
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
