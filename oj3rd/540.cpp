#include <cstdio>
int x, y, r;
int main()
{
	while(scanf("%d%d%d", &x, &y, &r) == 3)
		puts(x >= (r << 1) && y >= (r << 1) ? "Alice" : "Bob");
	return 0;
}
