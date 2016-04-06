#include <cstdio>
#include <algorithm>
using namespace std;
int n, s, a[1001], ans;
int main()
{
	while(scanf("%d%d", &n, &s) == 2)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		ans = 0;
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
			{
				int l = j + 1, r = n - 1;
				if(l > r)
					continue;
				while(l < r)
				{
					int m = l + r >> 1;
					if(a[i] + a[j] + a[m] > s)
						r = m;
					else
						l = m + 1;
				}
				ans += n - l;
			}
		printf("%d\n", ans);
	}
	return 0;
}
