#include <cstdio>

int main()
{
	int t, n, x;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		bool flag1 = 0, flag2 = 0;
		while(n--)
		{
			scanf("%d", &x);
			flag1 |= x == 1;
			flag2 |= x == 0;
		}
		puts(flag1 && flag2 ? "YES" : "NO");
	}
	return 0;
}
