#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int t, n, a[maxn];
bool pre[maxn], suf[maxn];
bool check()
{
	pre[0] = 1;
	for(int i = 1; i < n; ++i)
		pre[i] = pre[i - 1] && a[i - 1] <= a[i];
	suf[n - 1] = 1;
	for(int i = n - 2; i >= 0; --i)
		suf[i] = suf[i + 1] && a[i] <= a[i + 1];
	if(pre[n - 2] || suf[1])
		return 1;
	for(int i = 1; i < n - 1; ++i)
		if(pre[i - 1] && suf[i + 1] && a[i - 1] <= a[i + 1])
			return 1;
	return 0;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		if(check())
		{
			puts("YES");
			continue;
		}
		for(int i = 0, j = n - 1; i < j; ++i, --j)
			swap(a[i], a[j]);
		puts(check() ? "YES" : "NO");
	}
	return 0;
}
