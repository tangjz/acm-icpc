#include <cstdio>
int t, n, a[23333];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		a[0] = 0;
		for(int i = 2; i * i <= n; ++i)
			while(n % i == 0)
			{
				a[++a[0]] = i;
				n /= i;
			}
		if(n > 1)
			a[++a[0]] = n;
		printf("%d\n", a[0]);
		for(int i = 1; i < a[0]; ++i)
			printf("%d ", a[i]);
		printf("%d\n", a[a[0]]);
	}
	return 0;
}
