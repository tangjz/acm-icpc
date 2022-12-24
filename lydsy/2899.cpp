#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 51, mod = (int)1e9 + 7;
int n, nxt[maxn], ans;
vector<int> e[maxn];
map<vector<int>, int> Hash;
int getHash(vector<int> &vec) {
	map<vector<int>, int>::iterator it = Hash.find(vec);
	if(it != Hash.end())
		return it -> second;
	int ret = (int)Hash.size();
	Hash.insert(make_pair(vec, ret));
	return ret;
}
int dfs(int u) {
	vector<int> vec;
	vec.reserve(e[u].size());
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		vec.push_back(dfs(*it));
	sort(vec.begin(), vec.end());
	for(int i = 0, ctr; i < (int)vec.size(); ++i)
		if(!i || vec[i - 1] != vec[i]) {
			ctr = 1;
		} else {
			ans = (LL)ans * (++ctr) % mod;
		}
	return getHash(vec);
}
void solve() {
	int m = 0, idx[maxn] = {};
	bool sp[maxn] = {};
	vector<int> cir[maxn];
	for(int i = 1; i <= n; ++i) {
		// vector<int>().swap(e[i]);
		if(idx[i])
			continue;
		int j;
		for(j = i; !idx[j]; j = nxt[j])
			idx[j] = -1;
		if(idx[j] == -1) {
			++m;
			for(j = i; idx[j] == -1; j = nxt[j])
				idx[j] = m;
			for(int k = nxt[j]; k != j; k = nxt[k]) {
				sp[k] = 1;
				cir[m].push_back(k);
			}
			sp[j] = 1;
			cir[m].push_back(j);
		} else {
			for(int k = i; k != j; k = nxt[k])
				idx[k] = idx[j];
		}
	}
	for(int i = 1; i <= n; ++i)
		if(!sp[i])
			e[nxt[i]].push_back(i);
	vector<int> blocks;
	blocks.reserve(m);
	for(int i = 1; i <= m; ++i) {
		vector<int> vec;
		vec.reserve(cir[i].size());
		for(vector<int>::iterator it = cir[i].begin(); it != cir[i].end(); ++it)
			vec.push_back(dfs(*it));
		int ctr = 1;
		vector<int> res(vec.begin(), vec.end());
		for(int j = 1; j < (int)cir[i].size(); ++j) {
			vector<int> tmp;
			tmp.insert(tmp.end(), vec.begin() + j, vec.end());
			tmp.insert(tmp.end(), vec.begin(), vec.begin() + j);
			ctr += vec == tmp;
			if(res > tmp)
				res = tmp;
		}
		ans = (LL)ans * ctr % mod;
		blocks.push_back(getHash(res));
	}
	sort(blocks.begin(), blocks.end());
	for(int i = 0, ctr; i < (int)blocks.size(); ++i)
		if(!i || blocks[i - 1] != blocks[i]) {
			ctr = 1;
		} else {
			ans = (LL)ans * (++ctr) % mod;
		}
}
inline int mod_inv(int x) {
	return x <= 1 ? x : (mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod));
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", nxt + i);
	ans = 1;
	solve();
	ans = mod_inv(ans);
	for(int i = 1; i <= n; ++i)
		ans = (LL)ans * i % mod;
	printf("%d\n", ans);
	return 0;
}