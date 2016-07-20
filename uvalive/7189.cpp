#include <cstdio>
const int maxn = 101;
int t, n, x[maxn], y[maxn];
inline int det(int x1, int y1, int x2, int y2)
{
	return x1 * y2 - x2 * y1;
}
inline int len(int x, int y)
{
	return x * x + y * y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", x + i, y + i);
		if(n != 4)
		{
			puts("NO");
			continue;
		}
		bool flag = 0;
		for(int i = 0; i < n && !flag; ++i)
			for(int j = i + 1; j < n && !flag; ++j)
				for(int a = 0; a < n && !flag; ++a)
				{
					if(i == a || j == a)
						continue;
					int b = 6 - i - j - a;
					if(det(x[i] - x[j], y[i] - y[j], x[a] - x[b], y[a] - y[b]))
						continue;
					if(len(x[i] - x[j], y[i] - y[j]) != len(x[a] - x[b], y[a] - y[b]))
						continue;
					flag = 1;
				}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
