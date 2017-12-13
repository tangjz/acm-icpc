#include <set>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<int, int> Point;
const int maxn = 500001;
int n, p, q, r;
LL sum, ans;
vector<Point> e[maxn];
set<Point> sp;
int main() {
	scanf("%d%d%d%d", &n, &p, &q, &r);
	while(n--) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		e[p].push_back(make_pair(y, z));
		e[x].push_back(make_pair(q, z));
		e[x].push_back(make_pair(y, r));
	}
	sum = (LL)q * r;
	sp.insert(make_pair(0, r + 1));
	sp.insert(make_pair(q + 1, 0));
	for(int i = p; i >= 1; --i) {
		for(vector<Point>::iterator it = e[i].begin(); it != e[i].end(); ++it) {
			set<Point>::iterator jt = sp.lower_bound(*it), kt; // it -> first <= jt -> first
			if(jt -> second < it -> second) { // new point
				while(1) {
					jt = --sp.upper_bound(*it); // jt -> first <= it -> first
					if(it -> second < jt -> second)
						break;
					Point tp = *jt;
					sp.erase(jt);
					jt = kt = sp.lower_bound(tp);
					sum += (LL)(tp.first - (--jt) -> first) * (tp.second - kt -> second);
				}
				jt = kt = sp.lower_bound(*it);
				sum -= (LL)(it -> first - (--jt) -> first) * (it -> second - kt -> second);
				sp.insert(*it);
			}
		}
		ans += sum;
	}
	printf("%I64d\n", ans);
	return 0;
}
