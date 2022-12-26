#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)5e3 + 1, maxc = 26, mod = (int)1e9 + 7;
int n;
double p;
DB pw[maxn], f[maxn], g[maxn];
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		scanf("%d%lf", &n, &p);
		pw[0] = 1;
		for(int i = 1; i <= n; ++i)
			pw[i] = pw[i - 1] * (1 - p);
		f[0] = f[1] = g[0] = 0;
		g[1] = 1;
		for(int i = 2; i <= n; ++i) {
			f[i] = g[i] = i;
			for(int j = 1; j < i; ++j) {
				DB prb = (1 - pw[j]) / (1 - pw[i]);
				f[i] = min(f[i], 1 + (1 - prb) * f[i - j] + prb * (f[j] + g[i - j]));
			}
			for(int j = 1; j <= i; ++j) {
				DB prb = pw[j];
				g[i] = min(g[i], 1 + prb * g[i - j] + (1 - prb) * (f[j] + g[i - j]));
			}
		}
		printf("%.20f\n", (double)g[n]);
	}
	return 0;
}