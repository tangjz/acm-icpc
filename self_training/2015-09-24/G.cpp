#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 10, maxs = 15;
int n, rt, tot, idx;
LL ans;
pair<LL, LL> w[maxn][maxn], tmp;
bool vis[maxn];
char name[maxn][maxs], s[maxs], t[maxs];
int dcmp(pair<LL, LL> a, pair<LL, LL> b)
{
	if(a == b)
		return 0;
	return (double)a.first * b.second < (double)a.second * b.first ? -1 : 1;
}
int hh(char str[])
{
	for(int i = 0; i < tot; ++i)
		if(!strcmp(name[i], str))
			return i;
	vis[tot] = 0;
	strcpy(name[tot], str);
	return tot++;
}
void dfs(int u, pair<LL, LL> now)
{
	vis[u] = 1;
	if(u != rt)
	{
		LL res = (now.first - 1) / now.second + 1;
		if(res <= 100000)
		{
			pair<LL, LL> rmp = make_pair(res * now.second - now.first, now.first);
			LL r = __gcd(rmp.first, rmp.second);
			rmp.first /= r;
			rmp.second /= r;
			if(dcmp(rmp, tmp) < 0)
			{
				ans = res;
				idx = u;
				tmp = rmp;
			}
		}
	}
	for(int i = 0; i < tot; ++i)
		if(!vis[i] && w[u][i].second)
		{
			pair<LL, LL> rmp = make_pair(now.first * w[u][i].first, now.second * w[u][i].second);
			LL r = __gcd(rmp.first, rmp.second);
			rmp.first /= r;
			rmp.second /= r;
			dfs(i, rmp);
		}
}
int main()
{
	for(int Case = 1; scanf("%d", &n) == 1 && n; ++Case)
	{
		int x, y, r, u, v;
		tot = 0;
		memset(w, 0, sizeof w);
		while(n--)
		{
			scanf("%d%s%*s%d%s", &x, s, &y, t);
			u = hh(s);
			v = hh(t);
			r = __gcd(x, y);
			x /= r;
			y /= r;
			w[u][v] = make_pair(y, x);
			w[v][u] = make_pair(x, y);
		}
		ans = 0;
		tmp = make_pair(100, 1);
		scanf("%d%s", &x, s);
		dfs(rt = hh(s), make_pair(x, 1));
		printf("Case %d: %lld %s\n", Case, ans, name[idx]);
	}
	return 0;
}
