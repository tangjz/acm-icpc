#include <cstdio>
const int maxs = 1000001;
int n, x, cnt[maxs];
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		++cnt[x];
	}
	for(int i = maxs - 1; i >= 1; --i)
	{
		int tot = 0;
		for(int j = i; j < maxs && tot < 2; j += i)
			tot += cnt[j];
		if(tot >= 2)
		{
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
