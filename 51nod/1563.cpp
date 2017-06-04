#include <stdio.h>
#include <algorithm>
const int maxn = 200001;
int n;
std::pair<int, int> a[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		int x, w;
		scanf("%d%d", &x, &w);
		a[i] = std::make_pair(x - w, x + w);
	}
	std::sort(a, a + n);
	int ans = 0;
	for(int i = 0, p = -(~0U >> 1); i < n; ++i)
		if(p <= a[i].first)
		{
			++ans;
			p = a[i].second;
		}
	printf("%d\n", ans);
	return 0;
}
