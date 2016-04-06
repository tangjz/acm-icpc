#include <cstdio>
inline int Abs(int x) { return x < 0 ? -x : x; }
int n, x[3], y[3], s, Max[2], Min[2];
int main()
{
	scanf("%d", &n);
	Min[1] = ~0u >> 1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d%d%d%d%d", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2]);
		s = Abs((x[1] - x[0]) * (y[2] - y[0]) - (x[2] - x[0]) * (y[1] - y[0]));
		if(s >= Max[1]) Max[1] = s, Max[0] = i;
		if(s <= Min[1]) Min[1] = s, Min[0] = i;
	}
	printf("%d %d\n", Min[0], Max[0]);
	return 0;
}
