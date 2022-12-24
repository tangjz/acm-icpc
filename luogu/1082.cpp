#include <cstdio>
void gcd(int a, int b, int &x, int &y)
{
	if(!b) { x = 1; y = 0; return; }
	gcd(b, a % b, y, x);
	y -= a / b * x;
}
int main()
{
	int a, b, x, y;
	scanf("%d%d", &a ,&b);
	gcd(a, b, x, y);
	if(x < 0) x = (x + b) % b;
	printf("%d\n", x);
	return 0;
}