#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, a[maxn], id[maxn], ans[maxn][2];
bool cmp(const int &x, const int &y)
{
	return a[x] < a[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i), id[i] = i;
	sort(id, id + n, cmp);
	for(int i = 0; i < n; ++i)
	{
		ans[id[i]][0] = 0x7fffffff;
		if(i > 0)
			ans[id[i]][0] = min(ans[id[i]][0], a[id[i]] - a[id[i - 1]]);
		if(i < n - 1)
			ans[id[i]][0] = min(ans[id[i]][0], a[id[i + 1]] - a[id[i]]);
		ans[id[i]][1] = max(a[id[i]] - a[id[0]], a[id[n - 1]] - a[id[i]]);
	}
	for(int i = 0; i < n; ++i)
		printf("%d %d\n", ans[i][0], ans[i][1]);
	return 0;
}
