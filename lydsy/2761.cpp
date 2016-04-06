#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 50001;
int t, n, m, a[maxn], b[maxn];
bool vis[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		memcpy(b, a, n * sizeof(int));
		sort(b, b + n);
		m = unique(b, b + n) - b;
		memset(vis, 0, sizeof vis);
		vis[lower_bound(b, b + m, a[0]) - b] = 1;
		printf("%d", a[0]);
		for(int i = 1; i < n; ++i)
		{
			int j = lower_bound(b, b + m, a[i]) - b;
			if(!vis[j])
			{
				printf(" %d", a[i]);
				vis[j] = 1;
			}
		}
		putchar('\n');
	}
	return 0;
}
