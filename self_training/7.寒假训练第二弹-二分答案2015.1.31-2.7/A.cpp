#include <cstdio>
#include <cstring>
const int maxn = 131072;
int n, m, a[maxn], bit[maxn];
void add(int x, int val)
{
	for( ; x <= n; x += x & -x)
		bit[x] += val;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		memset(bit, 0, sizeof bit);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			add(i, a[i]);
		}
		scanf("%d", &m);
		while(m--)
		{
			int x, y, l, r, mid;
			char op[2];
			scanf("%s", op);
			if(op[0] == 'p')
			{
				scanf("%d%d", &x, &y);
				add(x, y - a[x]);
				a[x] = y;
			}
			else
			{
				scanf("%d", &x);
				l = 1, r = n;
				while(l < r)
				{
					mid = l + r >> 1;
					if(sum(mid) < x)
						l = mid + 1;
					else
						r = mid;
				}
				printf("%d\n", l);
			}
		}
	}
	return 0;
}
