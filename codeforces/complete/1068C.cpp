#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e3 + 1;
int n, m, cnt[2];
vector<pair<int, int> > seq[maxn];
int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		seq[u].push_back(make_pair(++cnt[0], ++cnt[1]));
		seq[v].push_back(cnt[0] < cnt[1] ? make_pair(++cnt[0], cnt[1]) : make_pair(cnt[0], ++cnt[1]));
	}
	for(int i = 1; i <= n; ++i) {
		if(!seq[i].size())
			seq[i].push_back(make_pair(++cnt[0], ++cnt[1]));
		int x = seq[i][0].first;
		for(auto p : seq[i])
			if(p.first != x)
				seq[i].push_back(make_pair(x, p.second));
		printf("%d\n", (int)seq[i].size());
		for(auto p : seq[i])
			printf("%d %d\n", p.first, p.second);
	}
	return 0;
}