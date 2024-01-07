#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e3 + 1, mod = (int)1e9 + 7;
int t, n, m, low[maxn], upp[maxn], ivs[maxn], f[2][maxn];
pair<int, int> seq[maxn];
inline int mod_inv(int x) {
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i < n; ++i) {
			scanf("%d%d", low + i, upp + i);
			ivs[i] = mod_inv(upp[i] - low[i] + 1);
		}
		low[n] = upp[n] = (int)1e6 + 1;
		ivs[n] = 1;
		for(int i = 1; i <= m; ++i)
			scanf("%d%d", &seq[i].first, &seq[i].second);
		sort(seq + 1, seq + m + 1);
		int tp = 0;
		for(int i = 1; i <= m; ++i)
			if(!tp || seq[tp].first < seq[i].first)
				seq[++tp] = seq[i];
			else
				seq[tp].second = seq[i].second;
		m = tp;
		int cur = 0, pre = 1;
		memset(f[cur], 0, (n + 1) * sizeof(int));
		f[cur][0] = 1;
		for(int i = 1; i <= m; ++i) {
			pre ^= 1;
			cur ^= 1;
			int pos = seq[i].first, hh = seq[i].second, sum = f[pre][0];
			f[cur][0] = 0;
			for(int j = 1; j <= n; ++j) {
				int succ = (LL)(max(min(hh, upp[j]), low[j] - 1) - low[j] + 1) * ivs[j] % mod;
				int fail = 1 - succ; fail < 0 && (fail += mod);
				f[cur][j] = j >= pos ? (LL)(sum + f[pre][j]) * fail % mod : 0;
				sum = ((LL)sum * succ + f[pre][j]) % mod;
				printf("%d%c", f[cur][j], " \n"[j == n]);
			}
		}
		int ans = 1 - f[cur][n]; ans < 0 && (ans += mod);
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}

