#include <cstdio>
int t, m;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%*d%d", &m);
		printf("1/%d\n", m);
	}
	return 0;
}
