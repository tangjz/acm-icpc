#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 20001;
int n, m, cnt[2], ans;
pair<int, int> a[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n - 1; ++i)
		scanf("%d", &a[i].first);
	for(int i = 0; i < m - 1; ++i)
	{
		scanf("%d", &a[i + n - 1].first);
		a[i + n - 1].second = 1;
	}
	sort(a, a + n + m - 2, greater<pair<int, int> >());
	cnt[0] = cnt[1] = 1;
	for(int i = 0; i < n + m - 2; ++i)
	{
		ans += cnt[a[i].second ^ 1] * a[i].first;
		++cnt[a[i].second];
	}
	printf("%d\n", ans);
	return 0;
}
