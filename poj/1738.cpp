#include <cstdio>
typedef long long LL;
const int maxn = 100001;
int t, n, tmp;
LL num[maxn], ans;
void dfs(int k)
{
	int i;
	LL sum = num[k - 1] + num[k];
	ans += sum;
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
	//scanf("%d", &t);
	//while(t--)
	while(scanf("%d", &n) == 1 && n)
	{
		//scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%lld", num + i);
		ans = 0;
		tmp = 1;
		for(int i = 1; i < n; ++i)
		{
			num[tmp++] = num[i];
			while(tmp >= 3 && num[tmp - 3] <= num[tmp - 1])
				dfs(tmp - 2);
		}
		while(tmp > 1)
			dfs(tmp - 1);
		printf("%lld\n", ans);
	}
	return 0;
}