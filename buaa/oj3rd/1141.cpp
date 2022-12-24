#include <cstdio>
int n, m;
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		if(n < m)
			swap(n, m);
		printf("%d\n", ((1 << n) - 1) * (1 << m));
	}
	return 0;
}
