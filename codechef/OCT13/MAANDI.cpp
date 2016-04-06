#include <cmath>
#include <cstdio>
int t, n, ans;
bool lucky(int x)
{
	while(x)
	{
		if(x % 10 == 4 || x % 10 == 7) return 1;
		x /= 10;
	}
	return 0;
}
int main()
{
	int i, j;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		ans = lucky(n);
		for(i = 2, j = (int)sqrt(n); i <= j; ++i)
			if(n % i == 0) ans += lucky(i) + lucky(n / i);
		if(j * j == n && lucky(j)) --ans;
		printf("%d\n", ans);
	}
	return 0;
}
