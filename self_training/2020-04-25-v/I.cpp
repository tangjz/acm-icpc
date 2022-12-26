#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)1e5 + 1, maxm = (int)5e5 + 1, mod = (int)1e9 + 7;
int n, m, val[maxn];
vector<int> e[maxn];
struct Event {
	static int pL, pR;
	int typ, u, v;
	void parse() {
		scanf("%d%d", &typ, &u);
		if(typ == 1) {
			v = --pL;
		} else if(typ == 2) {
			v = pR++;
		} else {
			scanf("%d", &v);
		}
	}
} eve[maxm];
int Event::pL, Event::pR;
bool cmp(int const &lft, int const &rht) {
	return eve[lft].v < eve[rht].v;
}
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		static int st = 0, tim[maxn] = {};
		n = Event::pL = Event::pR = 0;
		++st;
		scanf("%d", &m);
		for(int i = 0; i < m; ++i) {
			eve[i].parse();
			int &x = eve[i].u;
			if(tim[x] != st) {
				tim[x] = st;
				val[n++] = x;
				vector<int>().swap(e[x]);
			}
			e[x].push_back(i);
		}
		for(int i = 0; i < n; ++i) {
			int &o = val[i];
			static int tot, mx, ord[maxm], rnk[maxm], bit[maxm];
			tot = 0;
			for(int &id : e[o]) {
				Event &cur = eve[id];
				if(cur.typ != 3)
					ord[++tot] = id;
			}
			sort(ord + 1, ord + tot + 1, cmp);
			for(int j = 1; j <= tot; ++j) {
				rnk[ord[j]] = j;
				bit[j] = 0;
			}
			for(mx = 1; (mx << 1) <= tot; mx <<= 1);
			for(int &id : e[o]) {
				Event &cur = eve[id];
				if(cur.typ == 3) {
					int x = 0, k = cur.v;
					for(int y = mx, z; y > 0; y >>= 1)
						if((z = x | y) <= tot && bit[z] < k) {
							x = z;
							k -= bit[z];
						}
					for(++x; x <= tot; x += x & -x)
						--bit[x];
				} else {
					for(int x = rnk[id]; x <= tot; x += x & -x)
						++bit[x];
				}
			}
			for(int x = 1, y; x <= tot; ++x)
				if((y = x - (x & -x)) > 0)
					bit[x] += bit[y];
			vector<int> pos;
			bit[0] = 0;
			for(int x = tot; x > 0; --x) {
				bit[x] -= bit[x - 1];
				if(bit[x] > 0) {
					// assert(bit[x] == 1);
					int id = ord[x];
					pos.push_back(eve[id].v);
				}
			}
			e[o].swap(pos);
		}
		priority_queue<pair<int, int> > Q;
		for(int i = 0; i < n; ++i) {
			int &o = val[i];
			if(e[o].empty())
				continue;
			Q.push(make_pair(-e[o].back(), o));
		}
		while(!Q.empty()) {
			int o = Q.top().second;
			Q.pop();
			printf("%d\n", o);
			e[o].pop_back();
			if(!e[o].empty())
				Q.push(make_pair(-e[o].back(), o));
		}
	}
	return 0;
}