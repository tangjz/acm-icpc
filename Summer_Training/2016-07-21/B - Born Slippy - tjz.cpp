#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned int UL;
const int maxn = (1 << 16) + 10, maxd = 1 << 8, maxs = maxn * maxd + 10, mod = 1000000007;
int tot, idx[maxd][maxd], pos[maxs], pre[maxs];
int t, n, w[maxn], ans;
UL val[maxs], f[maxn];
char str[10];
vector<int> e[maxn];
inline UL opt(UL x, UL y)
{
	return	str[0] == 'A' ? (x & y) :
			str[0] == 'O' ? (x | y) :
							(x ^ y);
}
inline void upd(UL &x, UL y)
{
	if(x < y)
		x = y;
}
void dfs(int u)
{
	int wL = w[u] >> 8, wR = w[u] & (maxd - 1);
	f[u] = 0;
	for(int i = 0; i < maxd; ++i)
		if(idx[i][wR] != -1)
			upd(f[u], val[idx[i][wR]] + (opt(wL, i) << 8));
	for(int i = 0; i < maxd; ++i)
	{
		UL vv = f[u] + opt(wR, i);
		if(idx[wL][i] == -1 || val[idx[wL][i]] < vv)
		{
			val[tot] = vv;
			pos[tot] = u;
			pre[tot] = idx[wL][i];
			idx[wL][i] = tot++;
		}
	}
	f[u] += w[u];
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		dfs(*it);
	for(int i = 0; i < maxd; ++i)
		if(pos[idx[wL][i]] == u)
			idx[wL][i] = pre[idx[wL][i]];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%s", &n, str);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%u", w + i);
			vector<int>().swap(e[i]);
		}
		for(int i = 2; i <= n; ++i)
		{
			int fa;
			scanf("%d", &fa);
			e[fa].push_back(i);
		}
		tot = 0;
		memset(idx, -1, sizeof idx);
		dfs(1);
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			ans = (ans + (LL)i * f[i]) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
