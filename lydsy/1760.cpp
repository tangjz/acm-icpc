#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, upp[maxn];
vector<int> e[maxn];
set<pair<int, int> > sp[maxn];
map<pair<int, int>, int> Hash;
int dfs(int u, int fa) {
	int ret = 0;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v == fa)
			continue;
		ret += dfs(v, u);
		if(sp[u].size() < sp[v].size())
			sp[u].swap(sp[v]);
		for(set<pair<int, int> >::iterator it = sp[v].begin(); it != sp[v].end(); ++it) {
			int ctr = it -> second;
			set<pair<int, int> >::iterator jt = sp[u].lower_bound(make_pair(it -> first, 0));
			if(jt != sp[u].end() && jt -> first == it -> first) {
				ctr += jt -> second;
				sp[u].erase(jt);
				if(ctr == upp[it -> first])
					continue;
			}
			sp[u].insert(make_pair(it -> first, ctr));
		}
		set<pair<int, int> >().swap(sp[v]);
	}
	ret += !sp[u].size();
	return ret;
}
inline void update(int u, int v, int id) {
	pair<int, int> side = make_pair(u, v);
	map<pair<int, int>, int>::iterator it = Hash.find(side);
	if(it != Hash.end()) {
		e[id].push_back(it -> second);
		e[it -> second].push_back(id);
	} else {
		Hash[side] = id;
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n - 2; ++i) {
		int seq[4];
		scanf("%d%d%d%d", seq + 0, seq + 1, seq + 2, seq + 3);
		sort(seq, seq + 3);
		update(seq[0], seq[1], i);
		update(seq[0], seq[2], i);
		update(seq[1], seq[2], i);
		sp[i].insert(make_pair(seq[3], 1));
		++upp[seq[3]];
	}
	for(int i = 0; i < n - 2; ++i) {
		set<pair<int, int> >::iterator it = sp[i].begin();
		if(upp[it -> first] == it -> second)
			sp[i].erase(it);
	}
	printf("%d\n", dfs(0, -1) - 1);
	return 0;
}
