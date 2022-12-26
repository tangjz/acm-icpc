#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxd = 11, mod = (int)1e9 + 7;
int n, m, fa[maxn], f[maxn][maxd];
vector<int> e[maxn];
void merge(int Fu[], int Fv[]) { // (FF - 1) = (F - 1) G
	assert(Fu[0] == 1);
	assert(Fv[0] == 1);
	for(int i = maxd - 1; i > 0; --i) {
		LL tmp = Fu[i];
		for(int j = 1; j < i; ++j)
			tmp += (LL)Fv[j] * Fu[i - j];
		// tmp <= (maxd - 2) (mod - 1)^2 + (mod - 1) < 2^63
		Fu[i] = tmp % mod;
	}
}
void split(int Fu[], int Fv[]) { // (F - 1) = (FF - 1) G
	assert(Fu[0] == 1);
	assert(Fv[0] == 1);
	for(int i = 1; i < maxd; ++i) {
		LL tmp = Fu[i];
		for(int j = 1; j < i; ++j)
			tmp -= (LL)Fv[j] * Fu[i - j];
		// tmp >= -(maxd - 2) (mod - 1)^2 >= -2^63
		(Fu[i] = tmp % mod) < 0 && (Fu[i] += mod);
	}
}
void dfs(int u) {
	for(int v : e[u]) {
		dfs(v);
		merge(f[u], f[v]);
	}
}
int mod_inv(int x) {
	int y = mod, u = 1, v = 0, r;
	while(y) {
		r = x / y;
		swap(x, y);
		y -= r * x;
		swap(u, v);
		v -= r * u;
	}
	assert(x == 1);
	return u < 0 ? u + mod : u;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		f[i][0] = 1;
		scanf("%d", f[i] + 1);
	}
	for(int i = 2; i <= n; ++i) {
		scanf("%d", fa + i);
		e[fa[i]].push_back(i);
	}
	dfs(1);
	while(m--) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		static int pre[maxd], cur[maxd], tmp[maxd], arr[maxd];
		if(x == 0) {
			memcpy(pre, f[y], sizeof pre);
			int prd = (LL)z * mod_inv(f[y][1]) % mod;
			for(int i = 1; i < maxd; ++i)
				f[y][i] = (LL)f[y][i] * prd % mod;
			memcpy(cur, f[y], sizeof cur);
			for(int i = 2, u = fa[y]; i < maxd && u; ++i, u = fa[u]) {
				memcpy(tmp, f[u], sizeof tmp);
				split(f[u], pre);
				merge(f[u], cur);
				swap(pre, tmp);
				memcpy(cur, f[u], sizeof cur);
			}
		} else if(x == 1) {
			memcpy(pre, f[y], sizeof pre);
			memset(cur, 0, sizeof cur);
			cur[0] = 1;
			for(int i = 2, u = fa[y]; i < maxd && u; ++i, u = fa[u]) {
				memcpy(tmp, f[u], sizeof tmp);
				split(f[u], pre);
				merge(f[u], cur);
				swap(pre, tmp);
				memcpy(cur, f[u], sizeof cur);
			}
			fa[y] = z;
			memset(pre, 0, sizeof pre);
			pre[0] = 1;
			memcpy(cur, f[y], sizeof cur);
			for(int i = 2, u = fa[y]; i < maxd && u; ++i, u = fa[u]) {
				memcpy(tmp, f[u], sizeof tmp);
				split(f[u], pre);
				merge(f[u], cur);
				swap(pre, tmp);
				memcpy(cur, f[u], sizeof cur);
			}
		} else {
			int ans = f[y][z];
			memcpy(pre, f[y], sizeof pre);
			memset(cur, 0, sizeof cur);
			cur[0] = 1;
			for(int i = 2, u = fa[y]; i < maxd && u; ++i, u = fa[u]) {
				memcpy(tmp, f[u], sizeof tmp);
				memcpy(arr, f[u], sizeof arr);
				(ans += arr[z]) >= mod && (ans -= mod);
				split(arr, pre);
				merge(arr, cur);
				(ans -= arr[z]) < 0 && (ans += mod);
				swap(pre, tmp);
				swap(cur, arr);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
