/*
 * ͬ3229 
 */
#include <cstdio>
int n, num[50001], tmp, ans;
void dfs(int k)
{
	int i, sum = num[k - 1] + num[k];
	ans += sum;
	--tmp;
	for(i = k; i < tmp; ++i) num[i] = num[i + 1];
	for(i = k - 1; i > 0 && num[i - 1] < sum; --i) num[i] = num[i - 1];
	num[i] = sum;
	while(i >= 2 && num[i] >= num[i - 2])
	{
		int d = tmp - i;
		dfs(i - 1);
		i = tmp - d;
	}
}
int main()
{
	int i;
	while(scanf("%d", &n) && n)
	{
		for(i = 0; i < n; ++i) scanf("%d", num + i);
		tmp = 1, ans = 0;
		for(i = 1; i < n; ++i)
		{
			num[tmp++] = num[i];
			while(tmp >= 3 && num[tmp - 3] <= num[tmp - 1]) dfs(tmp - 2);
		}
		while(tmp > 1) dfs(tmp - 1);
		printf("%d\n", ans);
	}
	return 0;
}
