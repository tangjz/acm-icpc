#include <cstdio>
#include <cstring>
const int maxn = 1001;
int n, a[maxn], b[maxn], c[maxn * 10];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		memset(c, 0, sizeof c);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < n; ++i)
			scanf("%d", b + i);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(a[i] + b[j] <= 10 * n)
					++c[a[i] + b[j]];
		for(int i = 0; i <= 10 * n; ++i)
			if(c[i])
				printf("%d %d\n", i, c[i]);
	}
	return 0;
}
