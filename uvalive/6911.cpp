#include <set>
#include <cstdio>
#include <algorithm>
const int maxn = 100001;
int t, n, tot, a[maxn], b[maxn], c[maxn], ans;
std::set<int> Hash;
std::pair<int, int> seg[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		std::set<int>().swap(Hash);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", a + i, b + i, c + i);
			Hash.insert(a[i]);
		}
		tot = 0;
		for(int i = 0; i < n; ++i)
		{
			Hash.erase(a[i]);
			std::set<int>::iterator it = Hash.lower_bound(b[i]);
			if(it == Hash.end() || *it > c[i])
				seg[tot++] = std::make_pair(b[i], -c[i]);
			Hash.insert(a[i]);
		}
		ans = Hash.size();
		std::sort(seg, seg + tot);
		for(int i = tot - 1, pos = ~0u >> 1; i >= 0; --i)
			if((a[i] = -seg[i].second < pos))
				pos = -seg[i].second;
		n = 0;
		for(int i = 0; i < tot; ++i)
			if(a[i])
				seg[n++] = seg[i];
		// containing erased above
		for(int i = 0, j = 0; i < n; i = j, ++ans)
			for( ; j < n && seg[j].first <= -seg[i].second; ++j);
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
