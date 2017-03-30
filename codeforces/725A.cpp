#include <stdio.h>
#include <cstring>
const int maxn = 200010;
int n, que[maxn], L, R;
bool vis[maxn];
char str[maxn];
int main()
{
	scanf("%d%s", &n, str + 1);
	for(int i = 1; i < n; ++i)
		if(str[i] == '>' && str[i + 1] == '<')
		{
			que[R++] = i;
			vis[i] = 1;
			que[R++] = i + 1;
			vis[i + 1] = 1;
		}
	while(L < R)
	{
		int u = que[L++];
		if(u > 1 && !vis[u - 1] && str[u - 1] == '>')
		{
			que[R++] = u - 1;
			vis[u - 1] = 1;
		}
		if(u < n && !vis[u + 1] && str[u + 1] == '<')
		{
			que[R++] = u + 1;
			vis[u + 1] = 1;
		}
	}
	printf("%d\n", n - R);
	return 0;
}
