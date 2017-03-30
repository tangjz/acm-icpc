#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
#define x first
#define y second
const int maxn = 300010;
int n;
pair<LL, LL> a[maxn];
bool cmp(const pair<LL, LL> &a, const pair<LL, LL> &b)
{
	if(a.x != b.x)
		return a.x > b.x;
	return a.y < b.y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%I64d%I64d", &a[i].x, &a[i].y);
	sort(a + 1, a + n, cmp);
	int ans, pos, cnt = 0;
	multiset<LL> sp;
	for(pos = 1; pos < n && a[pos].x > a[0].x; ++pos)
		sp.insert(a[pos].y - a[pos].x + 1);
	ans = pos - cnt;
	while(sp.size() > 0)
	{
		multiset<LL>::iterator it = sp.begin();
		if(a[0].x < *it)
			break;
		a[0].x -= *it;
		sp.erase(it);
		for( ; pos < n && a[pos].x > a[0].x; ++pos)
			sp.insert(a[pos].y - a[pos].x + 1);
		++cnt;
		if(ans > pos - cnt)
			ans = pos - cnt;
	}
	printf("%d\n", ans);
	return 0;
}
