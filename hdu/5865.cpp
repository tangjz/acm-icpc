#include <bits/stdc++.h>
using namespace std;
const int maxn = 5001, maxm = (int)1e5 + 1, maxk = 301, maxl = 13, maxv = (int)1.6e6 + 1;
int n, m, q, sg[maxn], seq[maxk], pw3[maxl], f[maxv];
vector<int> e[maxn];
int dfs(int u) {
	if(sg[u] != -1)
		return sg[u];
	vector<int> mex;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		mex.push_back(dfs(*it));
	sort(mex.begin(), mex.end());
	unique(mex.begin(), mex.end());
	sg[u] = 0;
	for(vector<int>::iterator it = mex.begin(); it != mex.end() && *it == sg[u]; ++it, ++sg[u]);
	return sg[u];
}
void mod_inc(int &u, int v, int w) {
	for(int i = 0, tp = u; v; ++i, tp /= 3, v /= 3) {
		int dif = (tp + v * w) % 3 - tp % 3;
		u += dif * pw3[i];
	}
}
int main() {
	pw3[0] = 1;
	for(int i = 1; i < maxl; ++i)
		pw3[i] = pw3[i - 1] * 3;
	while(scanf("%d%d%d", &n, &m, &q) == 3) {
		memset(sg, -1, sizeof sg);
		memset(f, 0, sizeof f);
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
		}
		for(int i = 1; i <= n; ++i)
			dfs(i);
		for(int i = 1; i <= n; ++i) {
			int msk = 0;
			for(int j = 0; sg[i]; ++j, sg[i] >>= 1)
				if(sg[i] & 1)
					msk += pw3[j];
			sg[i] = msk;
		}
		int sum = 0, ans = 0;
		for(int i = 0; i < q; ++i) {
			scanf("%d", seq + i);
			mod_inc(sum, sg[seq[i]], 2);
		}
		for(int i = 0; i < q; ++i) {
			int u = seq[i], tp1 = sum;
			mod_inc(tp1, sg[u], 1);
			for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
				int tp2 = tp1;
				mod_inc(tp2, sg[*it], 2);
				ans += f[tp2] + !tp2;
			}
			for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
				int tp3 = sg[*it];
				mod_inc(tp3, sg[u], 2);
				++f[tp3];
			}
		}
		printf("%d\n", ans);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	return 0;
}
