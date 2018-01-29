#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxd = 43;
bool sp[maxd];
map<vector<LL>, LL> f[maxd];
LL solve(int dep, vector<LL> cur) {
	if(dep < 0 || !cur.size())
		return (LL)cur.size();
	if(f[dep].count(cur))
		return f[dep][cur];
	LL ret = 0, stp = 1LL << dep, sta = 0, las = 0;
	vector<LL> tmp;
	for(vector<LL>::iterator it = cur.begin(); it != cur.end(); ++it) {
		if(las + (stp << 3) < *it) {
			ret += solve(dep, tmp);
			vector<LL>().swap(tmp);
			sta = *it;
		}
		tmp.push_back(*it - sta);
		las = *it;
	}
	if(tmp.size()) {
		vector<LL> pre, nxt(tmp);
		if(sp[dep])
			for(int i = 1; i <= 4; ++i) {
				nxt.swap(pre);
				vector<LL>().swap(nxt);
				vector<LL>::iterator it = tmp.begin(), jt = pre.begin();
				while(it != tmp.end() || jt != pre.end())
					if(jt == pre.end() || (it != tmp.end() && *it + stp * i <= *jt)) {
						if(jt == pre.end() || *it + stp * i < *jt) {
							nxt.push_back(*(it++) + stp * i);
						} else {
							++it;
							++jt;
						}
					} else {
						nxt.push_back(*(jt++));
					}
			}
		ret += solve(dep - 1, nxt);
	}
	return f[dep][cur] = ret;
}
int main() {
	LL n = 1, ans = 0;
	for(int i = 1, mx = 0; i <= 18; ++i) {
		for(n *= 5; 1LL << mx <= n; ++mx);
		for(int j = 0; j < mx; ++j) {
			sp[j] = (n >> j) & 1;
			map<vector<LL>, LL>().swap(f[j]);
		}
		LL tmp = solve(mx - 1, vector<LL>(1));
		ans += tmp;
		printf("%d: %lld\n", i, tmp);
	}
	printf("%lld\n", ans);
	return 0;
}
