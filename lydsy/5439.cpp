#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxc = 3, maxd = maxc * maxc;
int t, n, nxt[maxc][maxn], pw[maxd];
char buf[maxn];
int main() {
	pw[0] = 1;
	for(int i = 1; i < maxd; ++i)
		pw[i] = pw[i - 1] * 3;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%s", &n, buf);
		for(int i = 0; i < maxc; ++i) {
			nxt[i][n] = n;
			for(int j = n - 1; j >= 0; --j)
				nxt[i][j] = buf[j] == 'a' + i ? j : nxt[i][j + 1];
		}
		LL ans = 0;
		for(int i = 1; i < maxc * maxc; ++i) {
			int low = (int)sqrt(ans * i);
			for( ; (LL)low * low > ans * i; --low);
			for( ; (LL)low * low <= ans * i; ++low);
			for(int j = 0; j < pw[i]; ++j) {
				static int seq[maxd];
				for(int k = 0, tp = j; k < i; ++k, tp /= 3)
					seq[k] = tp % 3;
				bool chk = 0;
				for(int d = 1; !chk && d < i; ++d) {
					if(i % d > 0)
						continue;
					chk = 1;
					for(int k = d; chk && k < i; ++k)
						chk &= seq[k] == seq[k - d];
				}
				if(chk)
					continue;
				int cnt = -1, pos = -1, upp = n;
				for(int k = 0; pos < n && low <= upp; (++k) == i && (k = 0), ++cnt) {
					++pos;
					upp -= nxt[seq[k]][pos] - pos;
					pos = nxt[seq[k]][pos];
				}
				cnt -= cnt % i;
				if(cnt >= low) {
					ans = (LL)cnt * cnt / i;
					low = cnt + 1;
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
