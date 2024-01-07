#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<pair<int, int> > > e(n, vector<pair<int, int> >());
	for(int i = 1; i < n; ++i) {
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		e[--u].push_back(make_pair(--v, d));
	}
	vector<pair<int, int> > info;
	vector<set<int> > adt(n, set<int>()), eve(n, set<int>());
	for(int i = 0; i < m; ++i) {
		int s, t;
		scanf("%d%d", &s, &t);
		info.push_back(make_pair(--s, t));
		adt[s].insert(i);
	}
	typedef long long LL;
	vector<pair<LL, LL> > seg, rseg;
	auto upd_seg = [&](int x, int y, LL adt, bool add = 1) {
		auto tmp = make_pair(info[x].second + adt, info[y].second + adt);
		if(add) {
			seg.push_back(tmp);
		} else {
			rseg.push_back(tmp);
		}
	};
	vector<int> dsu(n, -1);
	function<int(int)> dsu_find = [&](int u) {
		return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
	};
	auto dsu_check = [&](int x, int y) {
		return dsu_find(info[x].first) == dsu_find(info[y].first);
	};
	function<void(int, LL)> dfs = [&](int u, LL dis) {
		for(auto &it : e[u]) {
			int &v = it.first;
			dfs(v, dis + it.second);
			if(eve[u].size() < eve[v].size())
				eve[u].swap(eve[v]);
			typedef set<int>::iterator Iter;
			Iter vL = eve[v].begin();
			while(vL != eve[v].end()) {
				Iter uR = eve[u].lower_bound(*vL);
				if(uR != eve[u].begin()) {
					Iter uL = uR;
					--uL;
					if(uR != eve[u].end() && !dsu_check(*uL, *uR))
						upd_seg(*uL, *uR, dis, 0);
					upd_seg(*uL, *vL, dis);
				}
				if(uR == eve[u].end()) {
					eve[u].insert(vL, eve[v].end());
					vL = eve[v].end();
				} else {
					int upp = *uR;
					Iter vR = vL;
					while(vR != eve[v].end() && *vR < upp) {
						eve[u].insert(*vR);
						vL = vR++;
					}
					upd_seg(*vL, upp, dis);
					if(vR != eve[v].end() && !dsu_check(*vL, *vR))
						upd_seg(*vL, *vR, dis, 0);
					++vL;
				}
			}
			set<int>().swap(eve[v]);
		}
		if(!eve[u].empty()) {
			int low = *eve[u].begin();
			if(dsu_find(info[low].first) != e[u].back().first)
				seg.push_back(make_pair(0LL, info[low].second + dis));
		}
		eve[u].insert(adt[u].begin(), adt[u].end());
		set<int>().swap(adt[u]);
		for(auto &it : e[u])
			dsu[it.first] = u;
	};
	dfs(0, 0);
	sort(seg.begin(), seg.end());
	sort(rseg.begin(), rseg.end());
	auto it = seg.begin(), jt = it, kt = rseg.begin();
	while(it != seg.end()) {
		if(kt != rseg.end() && *it == *kt) {
			++kt;
		} else if(it == jt) {
			++jt;
		} else {
			*(jt++) = *it;
		}
		++it;
	}
	assert(kt == rseg.end());
	seg.erase(jt, seg.end());
	LL cur = 0, lim = -1;
	it = seg.begin();
	priority_queue<LL, vector<LL>, greater<LL> > Q;
	while(it != seg.end() || !Q.empty()) {
		if(Q.empty() && (it -> first) > cur)
			cur = it -> first;
		while(it != seg.end() && (it -> first) <= cur)
			Q.push((it++) -> second);
		LL upp = Q.top();
		Q.pop();
		if(cur >= upp) {
			lim = upp;
			break;
		}
		++cur;
	}
	int cnt = 0;
	if(lim == -1) {
		cnt += (int)seg.size();
	} else {
		for(auto &it : seg)
			cnt += it.second < lim;
	}
	printf("%lld %d\n", lim, cnt);
	return 0;
}