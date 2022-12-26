#include <cstdio>
int a, b; bool flag;
int main()
{
	scanf("%d", &a);
	if(a < 0) putchar('-'), a = -a;
	while(a) b = (b << 3) + (b << 1) + a % 10, a /= 10;
	printf("%d\n", b);
}
