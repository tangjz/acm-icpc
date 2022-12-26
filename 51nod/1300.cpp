#include <bits/stdc++.h>
using namespace std;
const int maxn = 51, maxm = 8, maxd = 1 << (maxm << 1) | 1, maxe = 390625 + 2, mod = (int)1e9 + 7;
int n, m, ord[maxn], len[maxn], fa[maxn], ptot, idx[maxn], etot, seq[maxe], sta[maxd], f[maxn][maxd];
pair<int, int> lim[maxm | 1];
bool ban[maxd];
char buf[maxn][maxn];
int main() {
	scanf("%d%d", &n, &m);
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i) {
		scanf("%s", buf[i]);
		len[i] = strlen(buf[i]);
		ord[i] = i;
		f[i][0] = 1;
	}
	sort(ord, ord + n + 1, [&](int const &u, int const &v) {
		return len[u] < len[v];
	});
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &lim[i].first, &lim[i].second);
		idx[++lim[i].first] = idx[++lim[i].second] = 1;
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j)
			if(len[fa[i]] < len[j] && len[j] < len[i] && strncmp(buf[i], buf[j], len[j]) == 0)
				fa[i] = j;
		if(idx[i])
			idx[i] = ++ptot;
	}
	for(int i = 1; i <= m; ++i) {
		lim[i].first = idx[lim[i].first];
		lim[i].second = idx[lim[i].second];
	}
	int all = 1 << ptot;
	for(int i = 0; i < all; ++i) {
		for(int j = 1; !ban[i] && j <= m; ++j)
			ban[i] |= ((i >> (lim[j].first - 1)) & 1) && !((i >> (lim[j].second - 1)) & 1);
		int pos = sta[i];
		if(!ban[i])
			for(int j = i; ; j = (j - 1) & i) {
				if(!ban[j] && !ban[i ^ j])
					seq[pos++] = j;
				if(!j)
					break;
			}
		sta[i + 1] = pos;
	}
	for(int i = n; i > 0; --i) {
		int u = ord[i];
		for(int j = all - 1; j >= 0; --j) {
			if(ban[j])
				continue;
			for(int k = 1; k < all; k <<= 1)
				if((j & k) && !ban[j ^ k])
					(f[u][j] += f[u][j ^ k]) >= mod && (f[u][j] -= mod);
		}
		int p = fa[u];
		for(int j = all - 1; j >= 0; --j) {
			long long tmp = 0;
			for(int it = sta[j]; it < sta[j + 1]; ++it) {
				int k = seq[it];
				tmp += (long long)f[u][k] * f[p][j ^ k];
				if(tmp < 0)
					tmp = (unsigned long long)tmp % mod;
			}
			f[p][j] = tmp < mod ? tmp : tmp % mod;
		}
	}
	int ans = f[0][all - 1];
	for(int i = n - ptot; i > 0; --i)
		ans = (long long)ans * i % mod;
	printf("%d\n", ans);
	return 0;
}
