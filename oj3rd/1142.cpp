#include <cstdio>
const int maxn = 1000010;
int n, m, que[maxn], pos[maxn], l, r;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		l = 0, r = -1;
		for(int i = 0, x; i < n; ++i)
		{
			scanf("%d", &x);
			que[++r] = x;
			pos[r] = i;
			while(l < r && pos[l] <= pos[r] - m)
				++l;
			while(l < r && que[r - 1] >= que[r])
			{
				que[r - 1] = que[r];
				pos[r - 1] = pos[r];
				--r;
			}
			printf("%d ", que[l]);
		}
		putchar('\n');
	}
	return 0;
}
