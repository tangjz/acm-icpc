#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxt = 41, maxn = 61, maxd = 11, maxs = (int)2e5 + 1;
const LL INF = (LL)1e18;
int t, n[maxt], gcd[maxn][maxn], sz[maxn], adt[maxn];
LL m[maxt], ans[maxt];
pair<LL, LL> pool[maxd][maxs], *seq[maxn];
stack<pair<LL, LL> *> idle;
int main() {
	scanf("%d", &t);
	int mx = 0;
	for(int i = 0; i < t; ++i) {
		scanf("%lld%d", m + i, n + i);
		mx = max(mx, n[i]);
	}
	for(int i = 0; i <= mx; ++i)
		gcd[0][i] = i;
	for(int i = 1; i <= mx; ++i)
		for(int j = 0; j <= mx; ++j)
			gcd[i][j] = i > j ? gcd[j][i] : gcd[i][j - i];
	for(int i = 0; i < maxd; ++i)
		idle.push(pool[i]);
	for(int i = 1; i < mx; ++i) {
		seq[0] = idle.top();
		idle.pop();
		sz[0] = 0;
		seq[0][sz[0]++] = make_pair((LL)i, 1LL);
		bool vis[maxn] = {};
		for(int j = i + 1; j <= mx; ++j) {
			LL upp = 0, lim[maxn];
			for(int k = 0; k < t; ++k)
				if(j < n[k]) {
					upp = max(upp, m[k]);
				} else if(j == n[k]) {
					for(int o = 0; o < j; ++o)
						lim[o] = m[k] * i * gcd[j][o] / j;
					for(int o = 0; o < sz[0]; ++o) {
						LL den = seq[0][o].first, num = lim[den % j];
						if(num >= den)
							ans[k] += num / den * seq[0][o].second;
					}
				}
			upp *= i;
			if(j == mx || vis[j])
				continue;
			for(int k = j; k < mx; k += j)
				vis[k] = 1;
			for(int k = 0; k < j; ++k) {
				adt[k] = j / gcd[j][k];
				if(seq[adt[k]] == NULL) {
					seq[adt[k]] = idle.top();
					idle.pop();
					sz[adt[k]] = 0;
				}
			}
			for(int k = 0; k < sz[0]; ++k) {
				int mul = adt[seq[0][k].first % j];
				if(mul == 1)
					continue;
				pair<LL, LL> &cur = seq[0][k];
				seq[1][sz[1]++] = cur;
				seq[mul][sz[mul]] = make_pair(cur.first * mul, -cur.second);
				if(seq[mul][sz[mul]].first <= upp)
					++sz[mul];
			}
			idle.push(seq[0]);
			seq[0] = NULL;
			priority_queue<pair<int, int> > Q;
			for(int k = 1; k <= j; ++k) {
				if(seq[k] == NULL)
					continue;
				if(!sz[k]) {
					idle.push(seq[k]);
					seq[k] = NULL;
				} else {
					Q.push(make_pair(-sz[k], k));
				}
			}
			while(!Q.empty()) {
				int u = Q.top().second;
				Q.pop();
				seq[0] = seq[u];
				sz[0] = sz[u];
				seq[u] = NULL;
				if(Q.empty())
					break;
				int v = Q.top().second;
				Q.pop();
				seq[u] = idle.top();
				idle.pop();
				sz[u] = 0;
				for(int L = 0, R = 0; L < sz[0] || R < sz[v]; ) {
					LL lft = L < sz[0] ? seq[0][L].first : INF;
					LL rht = R < sz[v] ? seq[v][R].first : INF;
					if(lft < rht) {
						seq[u][sz[u]++] = seq[0][L++];
					} else if(lft > rht) {
						seq[u][sz[u]++] = seq[v][R++];
					} else {
						LL coeff = seq[0][L++].second + seq[v][R++].second;
						if(coeff)
							seq[u][sz[u]++] = make_pair(lft, coeff);
					}
				}
				idle.push(seq[0]);
				idle.push(seq[v]);
				seq[0] = seq[v] = NULL;
				Q.push(make_pair(-sz[u], u));
			}
		}
		idle.push(seq[0]);
		seq[0] = NULL;
	}
	for(int i = 0; i < t; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
