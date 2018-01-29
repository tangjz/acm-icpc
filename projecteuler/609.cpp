#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e8 + 1, maxm = (int)8.4e7 + 1, maxd = 65, mod = (int)1e9 + 7;
int n, tot, c[maxn], pr[maxm], sum[maxd], ans;
int main() {
	while(scanf("%d", &n) == 1) {
		tot = 0;
		memset(c + 1, 0, n * sizeof(int));
		for(int i = 2; i <= n; ++i) {
			if(!c[i])
				pr[tot++] = c[i] = i;
			for(int j = 0, k; (k = i * pr[j]) <= n; ++j) {
				c[k] = pr[j];
				if(c[i] == pr[j])
					break;
			}
		}
		pr[tot] = n + 1;
		for(int i = 1; i <= n; ++i)
			c[i] = c[i - 1] + (i == c[i]);
		memset(sum, 0, sizeof sum);
		for(int i = 0; i < tot; ++i)
			for(int j = 0, v = pr[i], adt = pr[i + 1] - pr[i] - 1; (v = c[v]) > 0; ) {
				j += c[v] == c[v - 1];
				++sum[j];
				sum[j + 1] += adt;
			}
		ans = 1;
		for(int i = 0; i < maxd; ++i)
			if(sum[i])
				ans = (long long)ans * sum[i] % mod;
		printf("%d\n", ans);
	}
	return 0;
}
