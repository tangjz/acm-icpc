#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
const int maxn = 501;
DB f[2][maxn][maxn], logF[maxn];
int n, vL, vR, a[maxn], cur, pre = 1;
int main() {
	scanf("%d%d%d", &n, &vL, &vR);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	f[cur][0][0] = 1;
	for(int i = 0, upp = 0; i < n; ++i) {
		swap(cur, pre);
		int nxt = min(upp + a[i], vL);
		for(int j = 0; j <= i + 1; ++j)
			for(int k = 0; k <= nxt; ++k)
				f[cur][j][k] = 0;
		for(int j = 0; j <= i; ++j)
			for(int k = 0; k <= upp; ++k) {
				f[cur][j][k] += f[pre][j][k];
				if(k + a[i] <= nxt)
					f[cur][j + 1][k + a[i]] += f[pre][j][k];
			}
		upp = nxt;
	}
	DB ans = 0;
	for(int i = 1; i <= n; ++i)
		logF[i] = logF[i - 1] + log((DB)i);
	for(int i = 0; i < n; ++i) {
		for(int j = 1; j <= vL; ++j)
			f[cur][i][j] += f[cur][i][j - 1];
		DB ways = 0;
		for(int j = 0, k; j < n; ) {
			for(k = j; j < n && a[j] == a[k]; ++j);
			int L = vR - a[k], R = vL;
			if(L >= R)
				continue;
			DB cnt = 0;
			for(int pos = i, sgn = 1; pos >= 0 && R >= 0; --pos, sgn = -sgn, L -= a[k], R -= a[k])
				cnt += sgn * (f[cur][pos][R] - (L >= 0 ? f[cur][pos][L] : 0));
			ways += cnt * (j - k);
		}
		assert(ways >= 0);
		ans += ways * exp(logF[i] + logF[n - 1 - i] - logF[n]);
	}
	printf("%.20e\n", (double)(1 - ans));
	return 0;
}
