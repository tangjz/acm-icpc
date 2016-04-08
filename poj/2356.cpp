#include <cstdio>
const int maxn = 10001;
int n, x[maxn], Hash[maxn], sum, ans, pos;
int main()
{
	scanf("%d", &n);
	ans = n + 1;
	Hash[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", x + i);
		sum = (sum + x[i]) % n;
		if(Hash[sum] && ans > i - Hash[sum] + 1)
		{
			ans = i - Hash[sum] + 1;
			pos = i;
		}
		Hash[sum] = i + 1;
	}
	printf("%d\n", ans);
	for(int i = pos - ans + 1; i <= pos; ++i)
		printf("%d\n", x[i]);
	return 0;
}