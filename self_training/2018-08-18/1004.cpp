#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1, maxm = 5, mod = (int)1e9 + 7;
int t, n, m, path[maxm];
vector<vector<int> > sp;
vector<int> ways, p[maxn][maxm];
void dfs(vector<int> *arr, int dep) {
	if(dep == m) {
		sp.push_back(vector<int>(path, path + m));
		return;
	}
	for(int x : arr[dep]) {
		path[dep] = x;
		dfs(arr, dep + 1);
	}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &m, &n);
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < n; ++j) {
				int x;
				scanf("%d", &x);
				p[--x][i].push_back(j);
			}
		for(int i = 0; i < n; ++i)
			dfs(p[i], 0);
		int ans = 0, sz = sp.size();
		vector<int>(sz, 1).swap(ways);
		sort(sp.begin(), sp.end());
		for(int i = 0; i < sz; ++i) {
			for(int j = 0; j < i; ++j) {
				bool chk = 1;
				for(int k = 0; chk && k < m; ++k)
					chk &= sp[j][k] < sp[i][k];
				chk && (ways[i] += ways[j]) >= mod && (ways[i] -= mod);
			}
			(ans += ways[i]) >= mod && (ans -= mod);
		}
		printf("%d\n", ans);
		vector<vector<int> >().swap(sp);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				vector<int>().swap(p[i][j]);
	}
	return 0;
}
