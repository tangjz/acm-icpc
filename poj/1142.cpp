#include <cstdio>
int n;
void digit(int &ret, int x)
{
	for( ; x > 0; x /= 10)
		ret += x % 10;
}
bool valid(int n)
{
	int sum1 = 0, sum2 = 0;
	digit(sum1, n);
	for(int i = 2; (long long)i * i <= n; ++i)
		while(n % i == 0)
		{
			digit(sum2, i);
			n /= i;
		}
	if(n > 1)
		digit(sum2, n);
	return sum1 == sum2;
}
bool isprime(int n)
{
	if(n < 2)
		return 0;
	for(int i = 2; (long long)i * i <= n; ++i)
		if(n % i == 0)
			return 0;
	return 1;
}
int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		for(++n; isprime(n) || !valid(n); ++n);
		printf("%d\n", n);
	}
	return 0;
}#include <cstdio>
int n;
void digit(int &ret, int x)
{
	for( ; x > 0; x /= 10)
		ret += x % 10;
}
bool valid(int n)
{
	int sum1 = 0, sum2 = 0;
	digit(sum1, n);
	for(int i = 2; (long long)i * i <= n; ++i)
		while(n % i == 0)
		{
			digit(sum2, i);
			n /= i;
		}
	if(n > 1)
		digit(sum2, n);
	return sum1 == sum2;
}
bool isprime(int n)
{
	if(n < 2)
		return 0;
	for(int i = 2; (long long)i * i <= n; ++i)
		if(n % i == 0)
			return 0;
	return 1;
}
int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		for(++n; isprime(n) || !valid(n); ++n);
		printf("%d\n", n);
	}
	return 0;
}
