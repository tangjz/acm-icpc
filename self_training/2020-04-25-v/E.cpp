#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;
void conv(int len, int f[], int g[]) { // f = f * g
	static int res[maxn];
	memset(res + 1, 0, len * sizeof(int));
	for(int i = 1; i <= len; ++i)
		for(int j = i, k = 1; j <= len; j += i, ++k)
			res[j] = (res[j] + (LL)f[i] * g[k]) % mod;
	memcpy(f + 1, res + 1, len * sizeof(int));
}
int n, d, f[maxn], g[maxn];
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &d, &n);
		for(int i = 1; i <= n; ++i) {
			f[i] = 0;
			g[i] = 1;
		}
		bool fir = 1;
		f[1] = 1;
		while(d > 0) {
			if(d & 1) {
				if(fir) {
					memcpy(f + 1, g + 1, n * sizeof(int));
					fir = 0;
				} else {
					conv(n, f, g);
				}
			}
			if((d >>= 1) > 0)
				conv(n, g, g);
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			(ans += f[i]) >= mod && (ans -= mod);
		printf("%d\n", ans);
	}
	return 0;
}