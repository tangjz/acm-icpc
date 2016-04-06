#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, p[666], vis[666], l, r, que[666], val[666];
char g[666][666];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", &p[i]);
	for(int i = 0; i < n; ++i)
		scanf("%s", g[i]);
	for(int i = 0; i < n; ++i)
		if(!vis[i])
		{
			vis[i] = 1;
			l = r = 0;
			val[r] = p[i];
			que[r++] = i;
			while(l < r)
			{
				int u = que[l++];
				for(int v = 0; v < n; ++v)
					if(g[u][v] == '1' && !vis[v])
					{
						vis[v] = 1;
						val[r] = p[v];
						que[r++] = v;
					}
			}
			sort(que, que + r);
			sort(val, val + r);
			for(int j = 0; j < r; ++j)
				p[que[j]] = val[j];
		}
	for(int i = 0; i < n; ++i)
		printf("%d ", p[i]);
	puts("");
	return 0;
}
