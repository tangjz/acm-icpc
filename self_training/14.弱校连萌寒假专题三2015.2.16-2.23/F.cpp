#include <cstdio>
#include <cstring>
const int maxv = 100001;
int n, v, f[maxv];
int main()
{
	while(scanf("%d%d", &v, &n) == 2)
	{
		memset(f, -1, sizeof f);
		f[0] = 0;
		while(n--)
		{
			int c, w;
			scanf("%d%d", &c, &w);
			for(int i = 0; i <= v; ++i)
				if(f[i] >= 0)
					f[i] = c;
				else if(i >= w && f[i - w] > 0)
					f[i] = f[i - w] - 1;
		}
		for(int i = v; i >= 0; --i)
			if(f[i] >= 0)
			{
				printf("%d\n", i);
				break;
			}
	}
	return 0;
}
