/*
ID: tangjin2
LANG: C++
TASK: crypt1
*/
#include <cstdio>
int n, used[10], num[6], ans;
bool check()
{
	int tmp1 = ((num[0] * 10 + num[1]) * 10 + num[2]) * num[3];
	if(tmp1 >= 1000) return 0;
	int tmp2 = ((num[0] * 10 + num[1]) * 10 + num[2]) * num[4];
	if(tmp2 >= 1000) return 0;
	int tmp3 = tmp1 * 10 + tmp2;
	if(tmp3 >= 10000) return 0;
	while(tmp1)
	{
		if(!used[tmp1 % 10]) return 0;
		tmp1 /= 10;
	}
	while(tmp2)
	{
		if(!used[tmp2%10])return 0;
		tmp2 /= 10;
	}
	while(tmp3)
	{
		if(!used[tmp3 % 10]) return 0;
		tmp3 /= 10;
	}
	return 1;
}
void dfs(int dep)
{
	if(dep == 5)
	{
		if(check()) ++ans;
		return;
	}
	for(int i = 1; i <= 9; ++i)
		if(used[i])
		{
			num[dep] = i;
			dfs(dep + 1);
		}
}
int main()
{
	freopen("crypt1.in", "r", stdin);
	freopen("crypt1.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		++used[x];
	}
	dfs(0);
	printf("%d\n", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
