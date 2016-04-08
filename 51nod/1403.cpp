#include <stdio.h>
const int maxn = 1000001;
int n, bit[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		++bit[i - x];
		++bit[i];
	}
	for(int i = 1; i <= n; ++i)
	{
		bit[i] += bit[i - 1] - 1;
		printf("%d%c", bit[i], " \n"[i == n]);
	}
	return 0;
}
