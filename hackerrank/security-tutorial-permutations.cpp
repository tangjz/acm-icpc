#include <stdio.h>
const int maxn = 21;
int n, perm[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", perm + i);
	for(int i = 1; i <= n; ++i)
		printf("%d\n", perm[perm[i]]);
	return 0;
}
