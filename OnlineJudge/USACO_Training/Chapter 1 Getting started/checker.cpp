/*
ID: tangjin2
LANG: C++
TASK: checker
*/
#include <cstdio>
int n, num[25], ans;
bool vis1[25], vis2[25], vis3[25];
void dfs(int i)
{
	int j;
	if(i == n)
	{
		if(++ans <= 3)
		{
			for(j = 0; j < n - 1; ++j) printf("%d ", num[j] + 1);
			printf("%d\n", num[j] + 1);
		}
		return;
	}
	for(j = 0; j < n; ++j)
		if(!vis1[j] && !vis2[i + j] && !vis3[j - i + 13])
		{
			num[i] = j;
			vis1[j] = vis2[i + j] = vis3[j - i + 13] = 1;
			dfs(i + 1);
			vis1[j] = vis2[i + j] = vis3[j - i + 13] = 0;
		}
}
int main()
{
	freopen("checker.in", "r", stdin);
	freopen("checker.out", "w", stdout);
	scanf("%d", &n);
	dfs(0);
	printf("%d\n", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
