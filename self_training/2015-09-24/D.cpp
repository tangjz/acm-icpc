#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 6, maxs = 15504;
struct Node
{
	int a[maxn];
	bool operator < (const Node &x) const
	{
		for(int i = 0; i < maxn; ++i)
			if(a[i] != x.a[i])
				return a[i] < x.a[i];
		return 0;
	}
} e[maxs], tmp;
map<Node, int> Hash;
int tot;
void dfs(int dep, int res)
{
	if(dep == maxn - 1)
	{
		tmp.a[dep] = res;
		e[tot++] = tmp;
		return;
	}
	for(int i = 0; i <= res; ++i)
	{
		tmp.a[dep] = i;
		dfs(dep + 1, res - i);
	}
}
int main()
{
	dfs(0, 15);
	sort(e, e + tot);
	for(int i = 0; i < tot; ++i)
		Hash[e[i]] = i;
	char op[2];
	for(int Case = 1; scanf("%s", op) == 1 && op[0] != 'e'; ++Case)
		if(op[0] == 'm')
		{
			for(int i = 0; i < maxn; ++i)
				scanf("%d", &tmp.a[i]);
			printf("Case %d: %d\n", Case, Hash[tmp]);
		}
		else
		{
			int n;
			scanf("%d", &n);
			tmp = e[n];
			printf("Case %d: ", Case);
			for(int i = 0; i < maxn; ++i)
				printf("%d%c", tmp.a[i], " \n"[i == maxn - 1]);
		}
	return 0;
}
