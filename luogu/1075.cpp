#include <cmath>
#include <cstdio>
int n;
int main()
{
	scanf("%d", &n);
	for(int i = 2, j = (int)sqrt(n); i <= j; ++i)
		if(n % i == 0) { printf("%d\n", n / i); break; }
}
