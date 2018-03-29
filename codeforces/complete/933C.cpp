#include <bits/stdc++.h>
using namespace std;
typedef double DB;
typedef pair<DB, DB> Pair;
typedef pair<Pair, DB> Triple;
const int maxn = 5001, maxm = maxn * maxn;
const DB eps = 1e-9;
namespace std {
	bool operator < (Pair const &u, Pair const &v) {
		return u.first < v.first - eps || (u.first < v.first + eps && u.second < v.second - eps);
	}
}
int n, dsu[maxn], ans;
Triple c[maxn];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[v];
	dsu[u] = v;
}
vector<Pair> get_ins(Triple A, Triple B) {
	DB &Ax = A.first.first, &Ay = A.first.second, &Ar = A.second;
	DB &Bx = B.first.first, &By = B.first.second, &Br = B.second;
	vector<Pair> ret;
	DB dis2 = (Bx - Ax) * (Bx - Ax) + (By - Ay) * (By - Ay);
	if((Ar + Br) * (Ar + Br) < dis2 - eps || dis2 < (Ar - Br) * (Ar - Br) - eps)
		return ret;
	DB angle = atan2(By - Ay, Bx - Ax), delta = acos((dis2 + Ar * Ar - Br * Br) / (2.0 * sqrt(dis2) * Ar));
	ret.push_back((Pair){Ax + Ar * cos(angle + delta), Ay + Ar * sin(angle + delta)});
	if(delta < -eps || delta > eps)
		ret.push_back((Pair){Ax + Ar * cos(angle - delta), Ay + Ar * sin(angle - delta)});
	return ret;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%lf%lf%lf", &c[i].first.first, &c[i].first.second, &c[i].second);
	sort(c, c + n);
	n = unique(c, c + n) - c;
	memset(dsu, -1, n * sizeof(int));
	set<Pair> sp;
	for(int i = 0; i < n; ++i) {
		set<Pair> sq;
		for(int j = 0; j < n; ++j) {
			if(i == j)
				continue;
			vector<Pair> ins = get_ins(c[i], c[j]);
			for(vector<Pair>::iterator it = ins.begin(); it != ins.end(); ++it) {
				dsu_merge(i, j);
				sp.insert(*it);
				sq.insert(*it);
			}
		}
		ans += sq.size();
	}
	ans -= sp.size();
	for(int i = 0; i < n; ++i)
		ans += dsu_find(i) == i;
	printf("%d\n", ++ans);
	return 0;
}
