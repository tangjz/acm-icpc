#include <cstdio>
long long num = 600851475143ll;
int main()
{
	long long i, max = 1;
	for(i = 2; i * i <= num; ++i)
		if(num % i == 0)
		{
			max = i;
			while(num % i == 0) num /= i;
		}
	if(num > 1) max = num;
	printf("%lld\n", max);
	return 0;
}
