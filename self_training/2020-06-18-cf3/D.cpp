#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 50 + 1, maxd = 26 + 1;
const int mod = (int)1e9 + 7;


int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int ctr[maxd] = {};
		char buf[maxn];
		scanf("%s", buf);
		for(int i = 0; buf[i]; ++i)
			++ctr[(int)(buf[i] - 'a')];

		int m, dis[maxn];
		scanf("%d", &m);
		for(int i = 0; i < m; ++i)
			scanf("%d", dis + i);

		int rem = m;
		bool vis[maxn] = {};
		vector<vector<int> > seq;
		while(rem > 0) {
			vector<int> pos;
			for(int i = 0; i < m; ++i)
				if(!vis[i] && !dis[i]) {
					--rem;
					vis[i] = 1;
					pos.push_back(i);
				}
			assert(!pos.empty());
			seq.push_back(pos);
			for(int i = 0; i < m; ++i)
				if(!vis[i])
					for(int j : pos)
						dis[i] -= abs(i - j);
		}

		reverse(seq.begin(), seq.end());

		int pos = 0;
		for(auto &it : seq) {
			int sz = (int)it.size();
			for( ; pos < maxd && ctr[pos] < sz; ++pos);
			assert(pos < maxd);
			for(int x : it)
				buf[x] = 'a' + pos;
			++pos;
		}
		buf[m] = '\0';
		puts(buf);
		// printf("Case #%d:");
	}

	return 0;
}