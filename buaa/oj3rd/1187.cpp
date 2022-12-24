#include <cstdio>
int n, m;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
		puts(n % (m + 1) == 0 ? "LOSE" : "WIN");
	return 0;
}
