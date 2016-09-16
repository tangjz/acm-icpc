#include <map>
#include <set>
#include <list>
#include <queue>
#include <deque>
//#include <stack>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200010, maxa = 500010, mod = 1000000007;
int n, q, a[maxn][10], cnt[maxa], num, tmp;
long long tmpcnt, ans;
bool vis[maxn];
void pfs(int id, int o, int dep, int sum)
{
	if(dep == a[id][0])
	{
		if(sum > 0)
			cnt[tmp] += o;
		return;
	}
	pfs(id, o, dep + 1, sum);
	tmp *= a[id][dep + 1];
	pfs(id, o, dep + 1, sum + 1);
	tmp /= a[id][dep + 1];
}
void dfs(int id, int dep, int sum)
{
	if(dep == a[id][0])
	{
		if(sum > 0)
		{
			if(sum & 1)
				tmpcnt += cnt[tmp];
			else
				tmpcnt -= cnt[tmp];
		}
		return;
	}
	dfs(id, dep + 1, sum);
	tmp *= a[id][dep + 1];
	dfs(id, dep + 1, sum + 1);
	tmp /= a[id][dep + 1];
}
void add(int id, int o)
{
	if(!a[id][0])
	{
		cnt[1] += o;
		return;
	}
	tmp = 1;
	pfs(id, o, 0, 0);
}
int que(int id)
{
	if(!a[id][0])
	{
		return num - 1;
	}
	tmp = 1;
	tmpcnt = 0;
	dfs(id, 0, 0);
	return num - tmpcnt;
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		for(int j = 2; j <= x / j; ++j)
			if(x % j == 0)
			{
				a[i][++a[i][0]] = j;
				while(x % j == 0)
					x /= j;
			}
		if(x > 1)
			a[i][++a[i][0]] = x;
	}
	for(int i = 1, x; i <= q; ++i)
	{
		scanf("%d", &x);
		if(!vis[x])
		{
			vis[x] = 1;
			add(x, 1);
			++num;
			ans += que(x);
		}
		else
		{
			vis[x] = 0;
			ans -= que(x);
			--num;
			add(x, -1);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
