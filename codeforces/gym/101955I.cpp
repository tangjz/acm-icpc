#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1 << 11 | 1;
int t, mx, sz, lft[3], rht[3], f[3][maxn][maxn], cur, pre = 1;
LL g[2][maxn];
template<class T>
void FWT(int n, T x[], int flag) { // fwt(x) or ifwt(x)
	int sft = flag > 0 ? 0 : 1;
	for(int dt = 1; dt < n; dt <<= 1)
		for(int i = 0; i < n; i += dt << 1)
			for(int j = 0; j < dt; ++j) {
				T tp = x[i + j + dt];
				x[i + j + dt] = (x[i + j] - tp) >> sft;
				x[i + j] = (x[i + j] + tp) >> sft;
			}
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		mx = 0;
		sz = 1;
		memset(f, 0, sizeof f);
		memset(g[cur], 0, sizeof g[0]);
		for(int i = 0; i < 3; ++i)
			scanf("%d", lft + i);
		for(int i = 0; i < 3; ++i)
			scanf("%d", rht + i);
		for(int i = 0; i < 3; ++i) {
			mx = max(mx, max(lft[i], rht[i]));
			for( ; sz <= mx; sz <<= 1);
			for(int x = 0; x <= lft[i]; ++x)
				for(int y = 0; y <= rht[i]; ++y)
					++f[i][abs(x - y)][x ^ y];
		}
		LL ans = 0;
		for(int i = 0; i <= mx; ++i) {
			for(int j = 0; j < 3; ++j) {
				FWT(sz, f[j][i], 1);
				if(i > 0)
					for(int k = 0; k < sz; ++k)
						f[j][i][k] += f[j][i - 1][k];
			}
			swap(cur, pre);
			for(int j = 0; j < sz; ++j)
				g[cur][j] = (LL)f[0][i][j] * f[1][i][j] * f[2][i][j];
			FWT(sz, g[cur], -1);
			LL sum = 0;
			for(int j = sz - 1; j > 0; --j) {
				int k = i ^ j;
				sum += g[cur][k] - g[pre][k];
				ans += sum;
			}
		}
		printf("Case #%d: %llu\n", Case, ans);
	}
	return 0;
}
