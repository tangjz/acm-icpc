#include <cmath>
#include <cstdio>
int t, n;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", ((int)sqrt(n) + (int)sqrt(n / 2)) & 1);
	}
	return 0;
}
