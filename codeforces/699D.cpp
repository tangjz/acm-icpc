#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200010;
int n, a[maxn], fa[maxn], ans;
bool vis[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		fa[i] = i;
	}
	for(int i = 1; i <= n; ++i)
		if(find(i) != find(a[i]))
			fa[find(i)] = find(a[i]);
		else if(i != a[i])
		{
			a[i] = i;
			vis[i] = 1;
			++ans;
		}
	int cur = -1;
	for(int i = 1; i <= n; ++i)
		if(find(i) == i && !vis[i])
		{
			cur = i;
			break;
		}
	for(int i = 1; i <= n; ++i)
		if(find(i) == i)
		{
			if(cur == -1)
				cur = i;
			else if(cur != i)
			{
				a[i] = cur;
				if(!vis[i])
					++ans;
			}
		}
	printf("%d\n", ans);
	for(int i = 1; i <= n; ++i)
		printf("%d%c", a[i], " \n"[i == n]);
	return 0;
}
