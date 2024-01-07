#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxm = (int)1e2 + 1;
typedef long long LL;
LL t, n, m, q, h[maxm][maxn], top, hh[maxn], no[maxn], sum, ans;
char str[maxm][maxn];
int main() {
	scanf("%lld", &t);
	for(LL Case = 1; Case <= t; ++Case) {
		scanf("%lld%lld%lld", &n, &m, &q);
		for(LL i = 1; i <= m; ++i)
			memset(str[i] + 1, 0x3f, n * sizeof(char));
		while(q--) {
			LL x, y;
			scanf("%lld%lld", &y, &x);
			str[x][y] = 0;
		}
		for(LL i = 1; i <= m; ++i)
			for(LL j = 1; j <= n; ++j)
				h[i][j] = str[i][j] == str[i - 1][j] ? h[i - 1][j] + 1 : 1;
		ans = 0;
		for(LL i = 1; i <= m; ++i)
			for(LL j = 1; j <= n; ++j) {
				if(str[i][j] != str[i][j - 1]) {
					top = 0;
					no[top] = j - 1;
					sum = 0;
				}
				if(!str[i][j])
					continue;
				while(top > 0 && h[i][j] <= hh[top]) {
					sum -= hh[top] * (no[top] - no[top - 1]);
					--top;
				}
				hh[++top] = h[i][j];
				no[top] = j;
				sum += hh[top] * (no[top] - no[top - 1]);
				ans += sum;
			}
		printf("Case #%lld: %lld\n", Case, ans);
	}
	return 0;
}

