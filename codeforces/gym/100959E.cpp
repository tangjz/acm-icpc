#include <cstdio>
#include <algorithm>
const int maxn = 1001;
int n, a[maxn], ans;
long long sum;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	std::sort(a, a + n);
	for(int i = 0; i < n; ++i)
	{
		if(a[i] <= sum)
			continue;
		sum += a[i];
		++ans;
	}
	printf("%d\n", ans);
	return 0;
}
