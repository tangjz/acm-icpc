#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int n, k, d, x[maxn], ans;
int main()
{
	while(scanf("%d%d%d", &n, &k, &d) == 3)
	{
		ans = 0;
		for(int i = 0; i < n; ++i)
			scanf("%d", x + i);
		sort(x, x + n);
		for(int i = 0; i < n; ++i)
			if(x[i])
			{
				++ans;
				for(int j = i + 1; j < n; ++j)
					if(x[j] && (x[j] - x[i]) % d == 0)
						if((x[j] - x[i]) / d >= k)
							break;
						else
							x[j] = 0;
				x[i] = 0;
			}
		printf("%d\n", ans);
	}
	return 0;
}
