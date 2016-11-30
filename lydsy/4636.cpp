#include <set>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 40001;
int n, a[maxn], b[maxn], c[maxn], tot, que[maxn << 1];
vector<int> e[maxn << 1];
multiset<int> sp;
LL ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d%d", a + i, b + i, c + i);
		que[tot++] = a[i];
		que[tot++] = b[i];
	}
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 1; i <= n; ++i)
	{
		e[lower_bound(que, que + tot, a[i]) - que].push_back(c[i]);
		e[lower_bound(que, que + tot, b[i]) - que].push_back(-c[i]);
	}
	sp.insert(0);
	for(int i = 0; i + 1 < tot; ++i)
	{
		for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
			if(*it > 0)
				sp.insert(*it);
			else
				sp.erase(sp.find(-*it));
		ans += (LL)(que[i + 1] - que[i]) * *sp.rbegin();
	}
	printf("%lld\n", ans);
	return 0;
}
