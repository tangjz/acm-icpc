#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6, maxm = (int)2e7, mod = 123454321;
int tot, pr[maxn | 1], d[maxm | 1], sz;
struct Node {
	double adt;
	int pre, cnt, low, upp;
} que[maxn << 3 | 1];
struct Ref {
	int idx;
	bool operator < (const Ref &t) const {
		return que[idx].adt > que[t.idx].adt;
	}
} ;
priority_queue<Ref> Q;
void print(int res) {
	int ans = 1;
	for( ; que[res].cnt > maxn; res = que[res].pre)
		(ans <<= 1) >= mod && (ans -= mod);
	for(int i = que[res].cnt; i < maxn; ++i)
		(ans <<= 1) >= mod && (ans -= mod);
	for( ; res > 0; res = que[res].pre) {
		ans = (long long)ans * que[res].low % mod;
		for( ; res > 0 && que[res].cnt == que[que[res].pre].cnt; res = que[res].pre);
	}
	printf("%d\n", ans);
}
int main() {
	memset(d, -1, sizeof d);
	for(int i = 2; tot <= maxn; ++i) {
		if(d[i] == -1) {
			d[i] = tot;
			pr[tot++] = i;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxm; ++j) {
			d[k] = j;
			if(d[i] == j)
				break;
		}
	}
	pr[tot] = maxm;
	que[sz] = (Node){0.0, -1, 0, pr[maxn], pr[maxn]};
	Q.push((Ref){sz++});
	for(int i = 1; i < maxn; ++i) {
		int pos = Q.top().idx;
		Q.pop();
		// print(pos);
		que[sz] = (Node){que[pos].adt + log(pr[0]), pos, max(maxn, que[pos].cnt) + 1, pr[0], pr[0]};
		Q.push((Ref){sz++});
		int cur = que[pos].low, nxt = pr[d[cur] + 1];
		if(cur >= pr[1] && nxt <= que[pos].upp) {
			que[sz] = (Node){que[pos].adt - log(cur) + log(nxt), pos, que[pos].cnt, nxt, que[pos].upp};
			Q.push((Ref){sz++});
		}
		if(pr[1] <= que[pos].low) {
			que[sz] = (Node){que[pos].adt + log(pr[1]) - log(pr[0]), pos, que[pos].cnt + 1, pr[1], que[pos].low};
			Q.push((Ref){sz++});
		}
	}
	print(Q.top().idx);
	return 0;
}
