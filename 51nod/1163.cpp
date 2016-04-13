#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 50001;
int n, fa[maxn];
long long ans;
pair<int, int> a[maxn];
int find(int x)
{
	return fa[x] == -1 ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &a[i].second, &a[i].first);
	sort(a, a + n, greater<pair<int, int> >());
	memset(fa, -1, (n + 1) * sizeof(int));
	for(int i = 0; i < n; ++i)
		if(a[i].second > n)
			ans += a[i].first;
		else
		{
			int tim = find(a[i].second);
			if(tim > 0)
			{
				ans += a[i].first;
				fa[tim] = find(tim - 1);
			}
		}
	printf("%lld\n", ans);
	return 0;
}
