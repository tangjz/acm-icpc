#include <stdio.h>
const int maxn = 200001;
int n, perm[maxn], ctr[maxn], ans1, ans2;
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", perm + i);
	ans1 = 1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", ctr + i);
		ans1 ^= ctr[i];
	}
	for(int i = 1; i <= n; ++i)
	{
		if(vis[i])
			continue;
		++ans2;
		for(int j = perm[i]; !vis[j]; vis[j] = 1, j = perm[j]);
	}
	if(ans2 == 1)
		ans2 = 0;
	printf("%d\n", ans1 + ans2);
	return 0;
}
