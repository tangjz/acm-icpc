#include <stdio.h>
const int maxn = 1000001;
int n, m, q, p;
bool vis[maxn];
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	while(m--)
	{
		int x;
		scanf("%d", &x);
		vis[x] = 1;
	}
	p = 1;
	if(vis[p])
	{
		printf("%d\n", p);
		return 0;
	}
	while(q--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(u == p)
			p = v;
		else if(v == p)
			p = u;
		else
			continue;
		if(vis[p])
		{
			printf("%d\n", p);
			return 0;
		}
	}
	printf("%d\n", p);
	return 0;
}
