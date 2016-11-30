#include <cstdio>
const int maxn = 500;
int n, x[maxn], y[maxn], ans, xpos, ypos;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", x + i, y + i);
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			if(ans < (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]))
			{
				ans = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
				xpos = i;
				ypos = j;
			}
	printf("%d %d\n", xpos + 1, ypos + 1);
	return 0;
}
