#include <stdio.h>
const int maxn = 21;
int n, perm[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", perm + i);
	bool flag = 1;
	for(int i = 1; i <= n; ++i)
		flag &= perm[perm[i]] == i;
	puts(flag ? "YES" : "NO");
	return 0;
}
