#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, mod = 998244353, inv2 = (mod + 1) / 2;
int n, cnt[maxn], typ[maxn], ord[maxn], f[2][2][maxn];
vector<int> e[maxn];
bool vis[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		int par;
		scanf("%d%d%d", &par, cnt + i, typ + i);
		if(par) {
			e[par].push_back(i);
		} else {
			assert(!ord[1]);
			ord[1] = i;
			vis[i] = 1;
		}
	}
	for(int i = 1, tot = 1; i <= n; ++i) {
		int u = ord[i];
		for(int v : e[u])
			if(!vis[v])
				ord[++tot] = v;
	}
	for(int i = n; i >= 1; --i) {
		int u = ord[i], g[2][2][2], cur = 0, pre = 1;
		bool fir = 1;
		if((int)e[u].size() < cnt[u]) {
			int tp = 1;
			for(int prd = inv2, rem = cnt[u] - (int)e[u].size(); rem > 0; rem >>= 1, prd = (LL)prd * prd % mod)
				(rem & 1) && (tp = (LL)tp * prd % mod);
			assert(tp);
			g[cur][1][1] = tp;
			g[cur][0][1] = g[cur][1][0] = 0;
			g[cur][0][0] = 1 - tp;
			g[cur][0][0] < 0 && (g[cur][0][0] += mod);
			fir = 0;
		}
		for(int v : e[u])
			if(fir) {
				g[cur][0][0] = f[0][0][v];
				g[cur][0][1] = f[0][1][v];
				g[cur][1][0] = f[1][0][v];
				g[cur][1][1] = f[1][1][v];
				fir = 0;
			} else {
				swap(pre, cur);
				g[cur][1][1] = (LL)g[pre][1][1] * f[1][1][v] % mod;
				g[cur][1][0] = ((LL)(g[pre][1][0] + g[pre][1][1]) * (f[1][0][v] + f[1][1][v]) - g[cur][1][1]) % mod;
				g[cur][1][0] < 0 && (g[cur][1][0] += mod);
				g[cur][0][1] = ((LL)(g[pre][0][1] + g[pre][1][1]) * (f[0][1][v] + f[1][1][v]) - g[cur][1][1]) % mod;
				g[cur][0][1] < 0 && (g[cur][0][1] += mod);
				g[cur][0][0] = (1LL - g[cur][0][1] - g[cur][1][0] - g[cur][1][1]) % mod;
				g[cur][0][0] < 0 && (g[cur][0][0] += mod);
			}
		swap(g[cur][0][0], g[cur][1][1]);
		swap(g[cur][0][1], g[cur][1][0]);
		f[0][0][u] = g[cur][0][0];
		f[0][1][u] = g[cur][0][1];
		f[1][0][u] = g[cur][1][0];
		f[1][1][u] = g[cur][1][1];
		if(typ[u] != -1) {
			(f[0][typ[u]][u] += f[0][!typ[u]][u]) >= mod && (f[0][typ[u]][u] -= mod);
			f[0][!typ[u]][u] = 0;
			(f[1][typ[u]][u] += f[1][!typ[u]][u]) >= mod && (f[1][typ[u]][u] -= mod);
			f[1][!typ[u]][u] = 0;
		}
	}
	printf("%d\n", (f[0][0][ord[1]] + f[1][1][ord[1]]) % mod);
	return 0;
}