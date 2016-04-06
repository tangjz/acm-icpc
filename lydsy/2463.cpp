#include <cstdio>
int n;
int main()
{
	while(scanf("%d", &n) == 1 && n)
		puts(n & 1 ? "Bob" : "Alice");
	return 0;
}
