#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 205;
int n, col[maxn], que[maxn], L, R;
vector<int> e[maxn];
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int c, x;
		scanf("%d", &c);
		for(int j = 1; j <= c; ++j)
		{
			scanf("%d", &x);
			e[i].push_back(x);
			e[x].push_back(i);
		}
	}
	for(int i = 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j)
		{
			memset(col + 1, 0, n * sizeof(int));
			bool flag = 1;
			for(int k = 1; k <= n; ++k)
			{
				if(i == k || j == k || col[k])
					continue;
				L = R = 0;
				col[k] = 1;
				que[R++] = k;
				while(L < R)
				{
					int u = que[L++];
					for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
					{
						int v = *it;
						if(i == v || j == v || col[u] + col[v] == 3)
							continue;
						if(!col[v])
						{
							col[v] = 3 - col[u];
							que[R++] = v;
						}
						else
						{
							flag = 0;
							break;
						}
					}
					if(!flag)
						break;
				}
				if(!flag)
					break;
			}
			if(!flag)
				continue;
			puts("Hurrah!");
			return 0;
		}
	puts("Fired.");
	return 0;
}
