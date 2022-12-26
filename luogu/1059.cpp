#include <cstdio>
int n;
bool vis[1001];
int main()
{
	int num;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &num);
		vis[num] = 1;
	}
	n = 0;
	for(int i = 1; i <= 1000; ++i) if(vis[i]) ++n;
	printf("%d\n", n);
	for(int i = 1; i <= 1000; ++i) if(vis[i]) printf("%d ", i);
}
