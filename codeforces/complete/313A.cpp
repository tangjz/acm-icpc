#include <cstdio>
#include <cstring>
int n;
int main()
{
	scanf("%d", &n);
	if(n >= 0) printf("%d\n", n);
	else
	{
		if(n / 100 * 10 + n % 10 > n / 10) printf("%d\n", n / 100 * 10 + n % 10);
		else printf("%d\n", n / 10);
	}
	return 0;
}
