#include <stdio.h>
const int maxn = 21;
int n, perm[maxn], img[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", perm + i);
		img[perm[i]] = i;
	}
	for(int i = 1; i <= n; ++i)
		printf("%d\n", img[i]);
	return 0;
}
