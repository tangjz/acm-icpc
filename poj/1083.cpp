#include <cstdio>
#include <cstring>
const int maxn = 201;
int t, n, l, r, c[maxn], ans;
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		memset(c, 0, sizeof c);
		scanf("%d", &n);
		while(n--)
		{
			scanf("%d%d", &l, &r);
			l = l - 1 >> 1;
			r = r - 1 >> 1;
			if(l > r)
				swap(l, r);
			++c[l];
			--c[r + 1];
		}
		for(int i = 0; i < maxn - 1; ++i)
		{
			if(ans < c[i])
				ans = c[i];
			c[i + 1] += c[i];
		}
		printf("%d\n", ans * 10);
	}
	return 0;
}