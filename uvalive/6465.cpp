#include <cstdio>
const int maxn = 17;
int t, k, a[maxn], ans;
int main()
{
	scanf("%d", &t);
	a[0] = a[16] = -1;
	while(t--)
	{
		ans = -1;
		scanf("%d", &k);
		for(int i = 1; i <= 15; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= 15; ++i)
		{
			int min = a[i];
			for(int j = i; j <= 15; ++j)
			{
				if(min > a[j])
					min = a[j];
				if(min > a[i - 1] && min > a[j + 1])
					++ans;
			}
		}
		printf("%d %d\n", k, ans);
	}
	return 0;
}
