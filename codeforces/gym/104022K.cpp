#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 1 << 8 | 1, maxs = (int)1e7 + 1;

int main() {
	int n;
	static char buf[maxs + maxn + 1] = {}, *sta[maxn];
	static int tot = 0, idx[maxd] = {};
	scanf("%d", &n);
	sta[0] = buf;
	for(int i = 0; i < n; ++i) {
		scanf("%s", sta[i]);
		int len = strlen(sta[i]);
		for(int j = 0; j < len; ++j) {
			int o = sta[i][j];
			if(!idx[o])
				idx[o] = ++tot;
		}
		sta[i + 1] = sta[i] + len + 1;
	}

	static int ord[maxn], ans[maxn] = {};
	iota(ord, ord + n, 0);
	typedef struct { int dep, L, R, upp; } Node;
	queue<Node> que;
	que.push({0, 0, n, n});

	while(!que.empty()) {
		Node cur = que.front();
		que.pop();
		// skip case: single child
		if(cur.upp < n)
			while(true) {
				bool chk = 1;
				char ch = sta[ord[cur.L]][cur.dep];
				if(!ch)
					break;
				for(int i = cur.L + 1; chk && i < cur.R; ++i)
					chk &= sta[ord[i]][cur.dep] == ch;
				if(!chk)
					break;
				++cur.dep;
			}
		// if max(rt.time) <= cur and max(rt.fa.time) > cur
		queue<int> chd;
		static int st = 0, tim[maxd + 1] = {};
		static vector<int> bkt[maxd + 1];
		if(!(++st)) {
			memset(tim, 0, sizeof tim);
			++st;
		}
		for(int i = cur.L; i < cur.R; ++i) {
			int o = idx[(int)sta[ord[i]][cur.dep]];
			if(!o) {
				continue;
			}
			if(tim[o] != st) {
				tim[o] = st;
				vector<int>().swap(bkt[o]);
				chd.push(o);
			}
			bkt[o].push_back(ord[i]);
		}
		while(!chd.empty()) {
			int o = chd.front();
			chd.pop();
			int las = cur.L, upp = -1;
			for(int x: bkt[o]) {
				ord[cur.L++] = x;
				upp = max(upp, x);
			}
			que.push({cur.dep + 1, las, cur.L, upp});
			++ans[upp];
			--ans[cur.upp];
		}
	}
	for(int i = 0; i < n; ++i) {
		ans[i + 1] += ans[i];
		printf("%d\n", ans[i]);
	}
	return 0;
}
