#include <stdio.h>
const int maxn = 21;
int n, perm[maxn], img[maxn];
int main()
{
	bool flag = 1;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", perm + i);
		flag &= !img[perm[i]];
		img[perm[i]] = i;
	}
	puts(flag ? "YES" : "NO");
	return 0;
}
