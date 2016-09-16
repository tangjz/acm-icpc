#include <cstdio>
const int maxn = 101;
int n, a[maxn], sum;
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		sum += a[i];
	}
	sum /= n >> 1;
	for(int i = 1; i <= n; ++i)
	{
		if(vis[i])
			continue;
		for(int j = i + 1; j <= n; ++j)
			if(!vis[j] && a[i] + a[j] == sum)
			{
				vis[i] = vis[j] = 1;
				printf("%d %d\n", i, j);
				break;
			}
	}
	return 0;
}
