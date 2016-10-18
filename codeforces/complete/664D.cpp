#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> Edge;
const int maxn = 100010;
int n, m, L, R, que[maxn], col[maxn], ans[2], out[2][maxn];
vector<Edge> e[maxn];
bool vis[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v, w;
		char op[2];
		scanf("%d%d%s", &u, &v, op);
		w = op[0] == 'B';
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	ans[0] = ans[1] = 0;
	for(int wan = 0; wan < 2; ++wan)
	{
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
			{
				L = R = 0;
				que[R++] = i;
				vis[i] = 1;
				while(L < R)
				{
					int u = que[L++];
					for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
						if(!vis[it -> first])
						{
							que[R++] = it -> first;
							vis[it -> first] = 1;
						}
				}
				int counter = 0, flag = 1;
				col[que[0]] = 0;
				for(int j = 1; j < R; ++j)
					col[que[j]] = -1;
				for(int j = 0; j < R; ++j)
				{
					int u = que[j];
					for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
					{
						int v = it -> first, w = it -> second;
						if(col[v] == -1)
						{
							col[v] = col[u] ^ w ^ wan;
							if(col[v])
								++counter;
						}
						else if(col[u] ^ col[v] ^ w ^ wan)
						{
							flag = 0;
							break;
						}
					}
				}
				if(flag)
				{
					if(counter > R - counter)
					{
						for(int j = 0; j < R; ++j)
							col[que[j]] ^= 1;
						counter = R - counter;
					}
					for(int j = 0; j < R; ++j)
						if(col[que[j]])
							out[wan][ans[wan]++] = que[j];
				}
				else
				{
					ans[wan] = -1;
					break;
				}
			}
	}
	int idx = ans[0] == -1 || ans[1] != -1 && ans[0] > ans[1];
	printf("%d\n", ans[idx]);
	for(int i = 0; i < ans[idx]; ++i)
		printf("%d%c", out[idx][i], " \n"[i == ans[idx] - 1]);
	return 0;
}
