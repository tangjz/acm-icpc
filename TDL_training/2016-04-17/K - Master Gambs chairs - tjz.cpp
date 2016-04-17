#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, m, a[maxn], ans;
int main()
{
	scanf("%d%d", &n, &m);
	memset(a + 1, 0x3f, n * sizeof(int));
	for(int i = 0; i < n; ++i)
	{
		int x, w;
		scanf("%d%d", &x, &w);
		if(a[x] > w)
			a[x] = w;
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
		if(a[i] <= m)
		{
			m -= a[i];
			++ans;
		}
		else
			break;
	printf("%d\n", ans);
	return 0;
}
