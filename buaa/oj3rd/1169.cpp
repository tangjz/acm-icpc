#include <cstdio>
int n, m;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
		if((n & 1) && (m & 1))
			puts("watashi");
		else
			puts("ore");
	return 0;
}
