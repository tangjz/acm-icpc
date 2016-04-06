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
int n, t, nxt[66666], vis[66666], que[66666], l, r;
int main()
{
	scanf("%d%d", &n, &t);
	for(int i = 1; i < n; ++i)
	{
		scanf("%d", &nxt[i]);
		nxt[i] += i;
	}
	que[r++] = vis[1] = 1;
	while(l < r)
	{
		int now = que[l++];
		if(vis[nxt[now]])
			continue;
		vis[nxt[now]] = 1;
		if(vis[t])
			break;
		que[r++] = nxt[now];
	}
	puts(vis[t] ? "YES" : "NO");
	return 0;
}
