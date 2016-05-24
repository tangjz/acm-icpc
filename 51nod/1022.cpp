#include <cstdio>
const int maxn = 1001;
int n, a[maxn], num[maxn], tmp, cost, ans = ~0u >> 1;
void dfs(int k)
{
	int i, sum = num[k - 1] + num[k];
	cost += sum;
	--tmp;
	for(i = k; i < tmp; ++i)
		num[i] = num[i + 1];
	for(i = k - 1; i > 0 && num[i - 1] < sum; --i)
		num[i] = num[i - 1];
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
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
			num[j] = a[(i + j) % n];
		tmp = 1;
		cost = 0;
		for(int j = 1; j < n; ++j)
		{
			num[tmp++] = num[j];
			while(tmp >= 3 && num[tmp - 3] <= num[tmp - 1])
				dfs(tmp - 2);
		}
		while(tmp > 1)
			dfs(tmp - 1);
		if(ans > cost)
			ans = cost;
	}
	printf("%d\n", ans);
	return 0;
}
