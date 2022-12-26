#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = (int)3e5 + 1;
int n, m, sz[maxn];
vector<LL> seq[maxn];
struct Node {
	LL v;
	int x, y, z;
	bool operator < (Node const &t) const {
		return v < t.v;
	}
} ;
priority_queue<Node> Q;
bool cmp(vector<LL> const &u, vector<LL> const &v) {
	return u[1] < v[1];
}
int main() {
	scanf("%d%d", &n, &m);
	LL low = 0;
	for(int i = 0; i < n; ++i) {
		scanf("%d", sz + i);
		seq[i].reserve(sz[i]);
		for(int j = 0; j < sz[i]; ++j) {
			LL x;
			scanf("%lld", &x);
			seq[i].push_back(-x);
		}
		sort(seq[i].begin(), seq[i].end());
		low += seq[i][0];
		if(sz[i] == 1) {
			vector<LL>().swap(seq[i--]);
			--n;
		} else {
			for(int j = sz[i] - 1; j >= 0; --j)
				seq[i][j] -= seq[i][j - 1];
		}
	}
	sort(seq, seq + n, cmp);
	for(int i = 0; i < n; ++i)
		sz[i] = (int)seq[i].size();
	for(; !Q.empty(); Q.pop());
	Q.push((Node){-low, 0, 0, 0});
	for(int i = 0; i < m; ++i) {
		Node cur = Q.top();
		Q.pop();
		LL val = cur.v;
		int px = cur.x, py = cur.y, pz = cur.z;
		printf("%lld%c", val, " \n"[i == m - 1]);
		if(py + 1 < sz[px])
			Q.push((Node){val - seq[px][py + 1], px, py + 1, 0});
		if(px + 1 < n) {
			Q.push((Node){val - seq[px + 1][1], px + 1, 1, 1});
			if(pz == 1)
				Q.push((Node){val + seq[px][1] - seq[px + 1][1], px + 1, 1, 1});
		}
	}
	return 0;
}
