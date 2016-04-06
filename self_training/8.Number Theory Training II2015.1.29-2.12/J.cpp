#include <cmath>
#include <cstdio>
int n, x, ans;
bool isprime()
{
	for(int i = 2, j = (int)sqrt(x); i <= j; ++i)
		if(x % i == 0)
			return 0;
	return 1;
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		ans = 0;
		while(n--)
		{
			scanf("%d", &x);
			ans += isprime();
		}
		printf("%d\n", ans);
	}
	return 0;
}
