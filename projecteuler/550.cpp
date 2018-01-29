#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e7 + 1, maxs = 65, mod = 987654321;
int sg[maxn], mx, c[maxs];
bool vis[maxn][maxs];
int mod_pow(int x, LL k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int mod_add(int x, int y) {
	return (x += y) < mod ? x : x - mod;
}
int mod_sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}
void FWT_iterate(int x[], int len, int dt) {
	for(int i = 0; i < len; i += dt << 1)
		for(int j = 0; j < dt; ++j) {
			int t = x[i + dt + j];
			x[i + dt + j] = mod_sub(x[i + j], t);
			x[i + j] = mod_add(x[i + j], t);
		}
}
void FWT(int x[], int len, int flag) {
	if(flag > 0) {
		for(int i = 1; i < len; i <<= 1)
			FWT_iterate(x, len, i);
	} else {
		int inv_len = 1;
		for(int i = len >> 1; i > 0; i >>= 1, inv_len = inv_len * ((mod + 1LL) >> 1) % mod)
			FWT_iterate(x, len, i);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * inv_len % mod;
	}
}
int main() {
	int n;
	LL m;
	while(scanf("%d%lld", &n, &m) == 2) {
		mx = 1;
		memset(c, 0, sizeof c);
		for(int i = 2; i <= n; ++i) {
			bool *v1 = vis[i], v2[maxs] = {};
			for(int j = 0; j < maxs; ++j) if(v1[j])
				for(int k = 0; k < maxs; ++k) if(v1[k])
					v2[j ^ k] = 1;
			for(sg[i] = 0; v2[sg[i]]; ++sg[i]);
			for(++c[sg[i]]; mx <= sg[i]; mx <<= 1);
			for(int j = i << 1; j <= n; j += i)
				vis[j][sg[i]] = 1;
		}
		FWT(c, mx, 1);
		for(int i = 0; i < mx; ++i)
			c[i] = mod_pow(c[i], m);
		FWT(c, mx, -1);
		int ans = mod_pow(n - 1, m) - c[0];
		printf("%d\n", ans < 0 ? ans + mod : ans);
	}
	return 0;
}
