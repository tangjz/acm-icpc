#include <cstdio>
int t, n, k;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &k);
		if(n % 2 == 0 && k % 2 == 1)
			puts("F");
		else if(n % 2 == 0 && (k >> 1) % 2 == 0 || n % 2 == 1 && (k - 1 >> 1) % 2 == 1)
			puts("A");
		else
			puts("B");
	}
	return 0;
}
