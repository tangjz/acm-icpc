#include <map>
#include <cstdio>
using namespace std;
const int maxn = 5010;
int n, k, q, a[maxn], x, ans;
map<int, int> Hash;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		Hash[a[i]] = 1;
	}
	scanf("%d", &q);
	while(q--)
	{
		ans = ~0u >> 1;
		scanf("%d", &x);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j <= k; ++j)
			{
				if(x == a[i] * j)
					ans = min(ans, j);
				if(x < a[i] * j)
					break;
				for(int jj = 1; jj <= k - j; ++jj)
					if((x - a[i] * j) % jj == 0 && Hash.count((x - a[i] * j) / jj))
						ans = min(ans, j + jj);
			}
		if(ans > k)
			puts("-1");
		else
			printf("%d\n", ans);
	}
	return 0;
}
