#include <cstdio>
int n, x, y, a;
int main()
{
	scanf("%d%d%d", &n, &x, &y);
	while(n--)
	{
		scanf("%d", &a);
		long long L = 0, R = 1e15, M;
		while(L < R)
		{
			M = L + R >> 1;
			if(M / x + M / y < a)
				L = M + 1;
			else
				R = M;
		}
		if(L % x == 0 && L % y == 0)
			puts("Both");
		else
			puts(L % y == 0 ? "Vanya" : "Vova");
	}
	return 0;
}
