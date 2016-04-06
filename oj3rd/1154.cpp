#include <cstdio>
int n, sg;
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		sg = 0;
		for(int i = 0, x; i < n; ++i)
		{
			scanf("%d", &x);
			sg ^= x;
		}
		puts(sg ? "jhljx" : "0yang");
	}
	return 0;
}
