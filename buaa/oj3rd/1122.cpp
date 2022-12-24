#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 501;
int n, k, a[maxn], b[maxn];
int main()
{
	while(scanf("%d%d", &n, &k) == 2)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		sort(a + 1, a + n + 1);
		bool flag = 0;
		for(int i = 1; i <= n && !flag; ++i)
			if(a[i] > i)
				flag = 1;
		if(flag)
		{
			puts("bienaole");
			continue;
		}
		for(int i = 1; i <= n; ++i)
		{
			a[i] %= k;
			b[i] = i % k;
		}
		sort(a + 1, a + n + 1);
		sort(b + 1, b + n + 1);
		for(int i = 1; i <= n && !flag; ++i)
			if(a[i] != b[i])
				flag = 1;
		puts(flag ? "bienaole" : "zheyekeyi");
	}
	return 0;
}
