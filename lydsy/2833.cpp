#include <cstdio>
const int maxn = 1001;
int F[maxn][maxn];
int f(int x, int y)
{
	int &ret = F[x][y];
	if(ret)
		return ret;
	if(y == 1)
		return ret = 1;
	for(int i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		if(x % j == 0)
			ret += f(y, x / i);
	}
	return ret;
}
int main()
{
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", f(n, n));
	}
	return 0;
}
