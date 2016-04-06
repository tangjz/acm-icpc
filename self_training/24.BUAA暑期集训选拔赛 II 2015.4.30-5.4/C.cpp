#include <set>
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100086;
int n, k, a[maxn], tot, que[maxn], cnt[maxn];
set<int> s;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		que[i] = a[i];
	}
	sort(que, que + n);
	tot = unique(que, que + n) - que;
	for(int i = 0; i < k; ++i)
	{
		a[i] = lower_bound(que, que + tot, a[i]) - que;
		if(cnt[a[i]] == 1)
			s.erase(a[i]);
		++cnt[a[i]];
		if(cnt[a[i]] == 1)
			s.insert(a[i]);
	}
	if(s.size() > 0)
		printf("%d\n", que[*s.rbegin()]);
	else
		puts("Nothing");
	for(int i = k; i < n; ++i)
	{
		if(cnt[a[i - k]] == 1)
			s.erase(a[i - k]);
		--cnt[a[i - k]];
		if(cnt[a[i - k]] == 1)
			s.insert(a[i - k]);
		a[i] = lower_bound(que, que + tot, a[i]) - que;
		if(cnt[a[i]] == 1)
			s.erase(a[i]);
		++cnt[a[i]];
		if(cnt[a[i]] == 1)
			s.insert(a[i]);
		if(s.size() > 0)
			printf("%d\n", que[*s.rbegin()]);
		else
			puts("Nothing");
	}
	return 0;
}
