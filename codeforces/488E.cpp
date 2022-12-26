#include <cstdio>
int n;
long long inv[131072];
int main()
{
	scanf("%d", &n);
	if(n == 1)
		puts("YES\n1");
	else if(n == 4)
		puts("YES\n1\n3\n2\n4");
	else
	{
		for(int i = 2; i * i <= n; ++i)
			if(n % i == 0)
			{
				puts("NO");
				return 0;
			}
		puts("YES\n1");
		inv[1] = 1;
		for(int i = 2; i < n; ++i)
		{
			printf("%I64d\n", i * inv[i - 1] % n);
			inv[i] = (n - n / i) * inv[n % i] % n;
		}
		printf("%d\n", n);
	}
	return 0;
}

