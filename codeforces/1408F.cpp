#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;
const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)2e4 + 1, maxm = (int)1e6 + 1;

void solve() {
	int n;
	scanf("%d", &n);
	if(n <= 2) {
		puts("0");
		return;
	}

	static vector<int> ids[maxn];
	set<pair<int, int> > sp;
	vector<pair<int, int> > out;
	int mx = 0, tot = 0;
	for( ; 1 << mx <= n; ++mx);
	for(int i = mx - 1, sta = 0; i >= 0; --i) {
		if(!((n >> i) & 1))
			continue;
		int cnt = 1 << i;
		for(int step = 1; step < cnt; step <<= 1)
			for(int sft = 0; sft < cnt; sft += step << 1)
				for(int pos = 0; pos < step; ++pos)
					out.push_back({sta + sft + pos, sta + sft + pos + step});
		for(int i = 0; i < cnt; ++i)
			ids[tot].push_back(sta++);
		sp.insert({cnt, tot++});
	}
	while(sp.size() > 2) {
		bool hasSame = 0;
		pair<int, int> las = {-1, -1};
		for(pair<int, int> const &cur : sp) {
			if(las.first == cur.first) {
				int cnt = las.first, u = las.second, v = cur.second;
				for(int i = 0; i < cnt; ++i)
					out.push_back({ids[u][i], ids[v][i]});
				ids[v].insert(ids[v].end(), ids[u].begin(), ids[u].end());
				sp.erase({cnt, u});
				sp.erase({cnt, v});
				sp.insert({cnt << 1, v});
				hasSame = 1;
				break;
			}
			las = cur;
		}
		if(hasSame)
			continue;
		las = *sp.rbegin();
		pair<int, int> cur = *sp.begin();
		int cnt = cur.first, u = las.second, v = cur.second;
		for(int i = 0; i < cnt; ++i) {
			int adt = ids[u].back();
			ids[u].pop_back();
			out.push_back({adt, ids[v][i]});
			ids[v].push_back(adt);
		}
		sp.erase(las);
		sp.erase(cur);
		las.first -= cnt;
		cur.first += cnt;
		sp.insert(las);
		sp.insert(cur);
	}

	printf("%d\n", (int)out.size());
	for(auto &it : out)
		printf("%d %d\n", it.first + 1, it.second + 1);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}