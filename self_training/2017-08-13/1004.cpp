#include <queue>
#include <cstdio>
typedef long long LL;
const int maxn = 500001, mod = (int)1e9 + 7;
int fact[maxn], pw[maxn];
int n, a[maxn], b[maxn], cnt, ans;
LL m;
struct Node {
	int idx;
	bool operator < (Node const &t) const {
		return a[idx] > a[t.idx];
	}
};
std::priority_queue<Node> Q;
int main() {
	fact[0] = pw[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		pw[i] = 2LL * pw[i - 1] % mod;
	}
	while(scanf("%d%I64d", &n, &m) == 2) {
		for(int i = 0; i < n; ++i) {
			scanf("%d", a + i);
			b[i] = pw[i - (i > 0)];
		}
		ans = cnt = 0;
		m -= a[0];
		for(int i = 1; i < n; ++i)
			if(m < 0) {
				m -= a[i];
				while(!Q.empty()) {
					int id = Q.top().idx;
					if(m + a[id] >= 0)
						break;
					Q.pop();
					(cnt -= b[id]) < 0 && (cnt += mod);
				}
				ans = (ans + (LL)cnt * fact[n - i]) % mod;
			} else {
				m -= a[i];
				if(m < 0) { // only once
					for( ; !Q.empty(); Q.pop());
					for(int j = 0; j <= i; ++j)
						if(m + a[j] >= 0) {
							(cnt += b[j]) >= mod && (cnt -= mod);
							Q.push((Node){j});
						}
					ans = (ans + (LL)cnt * fact[n - i]) % mod;
				} else {
					ans = (ans + (LL)pw[i] * fact[n - i]) % mod;
				}
			}
		if(m >= 0)
			(ans += pw[n - 1]) >= mod && (ans -= mod);
		printf("%d\n", ans);
	}
	return 0;
}
