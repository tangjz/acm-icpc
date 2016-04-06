#include <cstdio>
#include <cstring>
int a, b, n, seq[3001], hash[3001];
int main()
{
	while(scanf("%d%d", &a, &b) == 2)
	{
		memset(hash, -1, sizeof hash);
		n = 0;
		printf("%d/%d = %d.", a, b, a / b);
		a %= b;
		hash[a] = n;
		while(1)
		{
			a *= 10;
			seq[++n] = a / b;
			if(hash[a %= b] == -1)
				hash[a] = n;
			else
				break;
		}
		for(int i = 1; i <= hash[a]; ++i)
			putchar('0' + seq[i]);
		putchar('(');
		for(int i = 1; i <= 50 && hash[a] + i <= n; ++i)
			putchar('0' + seq[hash[a] + i]);
		if(hash[a] + 50 < n)
			printf("...");
		printf(")\n   %d = number of digits in repeating cycle\n\n", n - hash[a]);
	}
	return 0;
}
