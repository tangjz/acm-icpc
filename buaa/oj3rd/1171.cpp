#include <cstdio>
long long n;
int main()
{
	while(scanf("%lld", &n) == 1)
	{
		n += 2;
		while(n % 3 == 0)
			n /= 3;
		while(n % 5 == 0)
			n /= 5;
		puts(n == 1 ? "Yes" : "No");
	}
	return 0;
}
