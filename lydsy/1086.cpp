/*
 * 题目没有要求省会最少，dfs即可，每次取够b个省立即添加省会，多余的省最多不超过b个，满足小于3b的条件
 */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int n, b, cnt, no[maxn], no2[maxn], s[maxn];
vector<int> g[maxn];
bool vis[maxn];
stack<int> Q;
int dfs(int u)
{
	vis[u] = 1;
	int sum = 0;
	Q.push(u);
	for(vector<int>::iterator it = g[u].begin(), jt = g[u].end(); it != jt; ++it)
		if(!vis[*it])
		{
			sum += dfs(*it);
			if(sum >= b)
			{
				no2[++cnt] = u; s[cnt] = sum;
				while(Q.top() != u)
				{
					no[Q.top()] = cnt;
					Q.pop();
				}
				sum = 0;
			}
		}
	return sum + 1;
}
int main()
{
	scanf("%d%d", &n, &b);
	for(int i = 1, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	if(n < b)
		puts("0");
	else if(n <= 3 * b)
	{
		puts("1");
		for(int i = 1; i < n; ++i)
			printf("1 ");
		puts("1");
		puts("1");
	}
	else
	{
		dfs(1);
		for(int i = 1; i <= n; ++i)
			if(!no[i]) no[i] = cnt, ++s[cnt];
		for(int i = 1; i <= cnt; ++i)
			if(s[i] < b || s[i] > 3 * b)
			{
				puts("0");
				return 0;
			}
		printf("%d\n", cnt);
		for(int i = 1; i < n; ++i)
			printf("%d ", no[i]);
		printf("%d\n", no[n]);
		for(int i = 1; i < cnt; ++i)
			printf("%d ", no2[i]);
		printf("%d\n", no2[cnt]);
	}
	return 0;
}
