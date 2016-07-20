#include <vector>
#include <cstdio>
using namespace std;
const int maxn = 100010;
int n, p, m, col[maxn], que[maxn], L, R, ans;
vector<int> e[maxn];
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d%d", &n, &p, &m);
	ans = p;
	while(p--)
	{
		int x;
		scanf("%d", &x);
		col[x] = 1;
	}
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(!col[u])
		{
			if(col[v])
			{
				L = R = 0;
				col[u] = 1;
				++ans;
				que[R++] = u;
				while(L < R)
				{
					u = que[L++];
					for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
						if(!col[*it])
						{
							col[*it] = 1;
							++ans;
							que[R++] = *it;
						}
				}
			}
			else
				e[v].push_back(u);
		}
		printf("%d\n", ans);
	}
	return 0;
}
