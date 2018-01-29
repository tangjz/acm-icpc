#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 61;
const LL mod = (LL)6e9;
LL f[maxn][8][2], tp[2] = {1, 0};
int main() {
	LL n;
	while(scanf("%lld", &n) == 1) {
		int mx = 0;
		for( ; 1LL << mx <= n; ++mx);
		for(int i = 0; i < mx; ++i) {
			int o = (n >> i) & 1;
			for(int j = 0; j < 8; ++j) {
				LL *CF = f[i][j];
				int xLim = j & 1 ? 1 : o, yLim = j & 2 ? 1 : o, zLim = j & 4 ? 1 : o;
				CF[0] = CF[1] = 0;
 				for(int x = 0; x <= xLim; ++x)
 					for(int y = 0; y <= yLim; ++y)
 						for(int z = 0; z <= zLim; ++z) {
 							if(x ^ y ^ z)
 								continue;
 							LL *PF = i ? f[i - 1][j | (x < xLim) | (y < yLim) << 1 | (z < zLim) << 2] : tp;
 							(CF[0] += PF[0]) >= mod && (CF[0] -= mod);
 							CF[1] = (CF[1] + ((__int128_t)(x + y + z) << i) * PF[0] + PF[1]) % mod;
 						}
			}
		}
		LL ans = (f[mx - 1][0][1] - (__int128_t)n * (n + 1) * 3) % mod, ways = (f[mx - 1][0][0] - n * 3 - 1) % mod;
		LL nn = n - !(n & 1);
		ans = ((ans - ways * 3) / 6 - (__int128)nn * (nn - 1) / 2) % (mod / 6);
		printf("%lld\n", ans < 0 ? ans + mod / 6 : ans);
	}
	return 0;
}
