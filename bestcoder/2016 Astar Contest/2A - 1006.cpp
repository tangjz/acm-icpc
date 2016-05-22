#include <queue>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int t, n, m, deg[maxn], que[maxn];
vector<int> e[maxn];
priority_queue<int> Q;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		memset(deg + 1, 0, n * sizeof(int));
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			++deg[v];
		}
		for( ; !Q.empty(); Q.pop());
		for(int i = 1; i <= n; ++i)
			if(!deg[i])
				Q.push(i);
		for(int i = 1; i <= n; ++i)
		{
			que[i] = Q.top();
			Q.pop();
			for(vector<int>::iterator it = e[que[i]].begin(); it != e[que[i]].end(); ++it)
				if(!(--deg[*it]))
					Q.push(*it);
		}
		long long ans = 0;
		for(int i = 1, mx = n; i <= n; ++i)
		{
			if(mx > que[i])
				mx = que[i];
			ans += mx;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
