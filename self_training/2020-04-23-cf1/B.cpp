#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)2e3 + 1, maxd = 10, mod = (int)1e9 + 7;
const char *pat[] = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};
int n, m, c[maxn][maxd + 1];
char buf[maxn];
bitset<maxn> dp[maxn];
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i) {
			scanf("%s", buf);
			for(int j = 0; j < maxd; ++j) {
				c[i][j] = 0;
				for(int k = 0; buf[k]; ++k)
					if(buf[k] > pat[j][k]) {
						c[i][j] = m + 1;
						break;
					} else {
						c[i][j] += buf[k] < pat[j][k];
					}
			}
		}
		dp[n].reset();
		dp[n].set(0);
		for(int i = n - 1; i >= 0; --i) {
			dp[i].reset();
			for(int j = 0; j < maxd; ++j)
				dp[i] |= dp[i + 1] << c[i][j];
		}
		if(!dp[0].test(m)) {
			puts("-1");
			continue;
		}
		for(int i = 0; i < n; ++i)
			for(int j = maxd - 1; j >= 0; --j)
				if(m >= c[i][j] && dp[i + 1].test(m - c[i][j])) {
					buf[i] = '0' + j;
					m -= c[i][j];
					break;
				}
		buf[n] = '\0';
		puts(buf);
	}
	return 0;
}