/*
Author: tangjz
Complexity: O(n log log n)
Solution:
	Applying Burnside's lemma on it, we can split the circle into several blocks,
and we only need to care about edges within one block or between two adjacent blocks.
	Denote dp(d, m, 0/1) as the number of valid scenes for d blocks, where each
group contains exactly m points, and whether or not the leftmost two points of
each group must be connected. Then we have
	1. dp[1][i][j] = dp[1][i-1][0] + sum(dp[1][i-k+2][1] * dp[1][k-1][0], k=j+2..i);
	2. dp[2][i][j] = dp[2][i-1][0] + sum(dp[2][i-k+2][1] * dp[1][k-1][0], k=j+2..i)
		+ sum(dp[1][i-k+2][1] * dp[2][k-1][0], k=1..i);
	3. dp[d][i][j] = dp[2][i][j], when d>2.
	We can observe that
	1. dp[d][i][0] = 2 * dp[d][i][1], when i>1;
	2. dp[1][i][0] = A054726(i) = 2^i * LittleSchroeder[i-2], when i>1;
	3. dp[2][i][0] = A152254(i) = 2^i * CentralDelannoy[i-1], when i>0;
	4. LittleSchroeder[i] = (CentralDelannoy[i+1] - 3 * CentralDelannoy[i]) / (4 * i), when i>0.
	The answer is (sum(phi[d] * dp[min(d,2)][n/d], d|n) / n), which can be computed by
another dp in time complexity O(n log log n).
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
int inv[maxn], f[maxn], g[maxn], a[maxn], b[maxn];
inline void mod_fix(int &x) {
	x < 0 && (x += mod);
}
int main() {
	inv[1] = f[0] = f[1] = g[0] = 1;
	g[1] = 2;
	for(int i = 2; i < maxn; ++i) {
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		f[i] = ((12LL * i - 30) * f[i - 1] - (4LL * i - 16) * f[i - 2]) % mod * inv[i - 1] % mod;
		g[i] = ((12LL * i - 18) * g[i - 1] - (4LL * i -  8) * g[i - 2]) % mod * inv[i - 1] % mod;
		mod_fix(f[i]);
		mod_fix(g[i]);
	}
	memcpy(a, g, sizeof a);
	memset(b, -1, sizeof b);
	for(int i = 2; i < maxn; ++i)
		if(b[i] == -1)
			for(int j = i, k = 1; j < maxn; j += i, ++k) {
				int adt = k % i > 0 ? a[k] : b[k];
				a[j] = (a[j] + (i - 1LL) * adt) % mod;
				(b[j] = a[j] + adt) >= mod && (b[j] -= mod);
			}
	for(int i = 1; i < maxn; ++i) {
		f[i] = (LL)(f[i] + a[i] - g[i]) * inv[i] % mod;
		mod_fix(f[i]);
	}
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
