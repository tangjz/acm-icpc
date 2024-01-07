#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)51, maxm = (int)1e3 + 1, mod = (int)1e9 + 7;
int n, m, tot, pw[maxn];
LL vec[maxm];
pair<LL, int> seq[maxm];
int main() {
	pw[0] = 1;
	for(int i = 1; i < maxn; ++i)
		(pw[i] = pw[i - 1] << 1) >= mod && (pw[i] -= mod);
	while(scanf("%d%d", &n, &m) == 2) {
		memset(vec, 0, m * sizeof(LL));
		for(int i = 0; i < n; ++i) {
			static char buf[maxm];
			scanf("%s", buf);
			for(int j = 0; j < m; ++j)
				vec[j] = vec[j] << 1 | (buf[j] == '1');
		}
		sort(vec, vec + m);
		tot = 0;
		for(int i = 0; i < m; ++i)
			if(!tot || seq[tot - 1].first < vec[i])
				seq[tot++] = make_pair(vec[i], 1);
			else
				++seq[tot - 1].second;
		int zero = seq[0].first ? 0 : seq[0].second;
		int way0 = zero * zero * zero;
		int way1 = 0;
		for(int i = zero > 0; i < tot; ++i) {
			int tmp = seq[i].second + zero;
			way1 += tmp * tmp * tmp - way0;
		}
		int way2 = 0;
		for(int i = zero > 0; i < tot; ++i)
			for(int j = i + 1; j < tot; ++j) {
				way2 += 3 * seq[i].second * seq[j].second * ((zero << 1) + seq[i].second + seq[j].second);
				LL msk = seq[i].first ^ seq[j].first;
				int k = lower_bound(seq, seq + tot, make_pair(msk, 0)) - seq;
				if(j < k && seq[k].first == msk)
					way2 += 6 * seq[i].second * seq[j].second * seq[k].second;
			}
		int way3 = m * m * m - way0 - way1 - way2;
		int ans = (LL)way0 * pw[n] % mod;
		n > 0 && (ans = (ans + (LL)way1 * pw[n - 1]) % mod);
		n > 1 && (ans = (ans + (LL)way2 * pw[n - 2]) % mod);
		n > 2 && (ans = (ans + (LL)way3 * pw[n - 3]) % mod);
		printf("%d\n", ans);
	}
	return 0;
}
