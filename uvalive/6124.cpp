#include <cstdio>
int t, seq[7][6], out[7][6], id[7];
bool vis[7];
bool check(int dep)
{
	return (dep < 1 || out[dep][(dep + 2) % 6] == out[0][(dep + 5) % 6])
		&& (dep < 2 || out[dep][(dep + 3) % 6] == out[dep - 1][dep % 6])
		&& (dep < 6 || out[dep][1] == out[1][4]);
}
bool dfs(int dep)
{
	if(dep == 7)
		return 1;
	for(int i = 0; i < 7; ++i)
		if(!vis[i])
		{
			vis[i] = 1;
			id[dep] = i;
			for(int j = 0; j < 6; ++j)
			{
				if(!dep && seq[i][j] != 1)
					continue;
				for(int k = 0; k < 6; ++k)
					out[dep][k] = seq[i][(j + k) % 6];
				if(!check(dep))
					continue;
				if(dfs(dep + 1))
				{
					vis[i] = 0;
					return 1;
				}
			}
			vis[i] = 0;
		}
	return 0;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		for(int i = 0; i < 7; ++i)
			for(int j = 0; j < 6; ++j)
				scanf("%d", seq[i] + j);
		if(dfs(0))
		{
			printf("Case %d: ", Case);
			for(int i = 0; i < 7; ++i)
				printf("%d%c", id[i], " \n"[i == 6]);
		}
		else
			printf("Case %d: No solution\n", Case);
	}
	return 0;
}
