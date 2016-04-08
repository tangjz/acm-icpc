#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> seg;
const int maxn = 100010;
int n, cnt, tot, r[maxn], f[maxn];
seg e[maxn];
pair<seg, int> l[maxn];
bool cmp(const pair<seg, int> &x, const pair<seg, int> &y)
{
	return x.first.second < y.first.second;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(x + y > n)
			continue;
		e[cnt++] = make_pair(x + 1, n - y);
	}
	if(!cnt)
	{
		printf("%d\n", n);
		return 0;
	}
	sort(e, e + cnt);
	l[++tot] = make_pair(e[0], 1);
	for(int i = 1; i < cnt; ++i)
		if(e[i - 1] != e[i])
			l[++tot] = make_pair(e[i], 1);
		else if(l[tot].second < l[tot].first.second - l[tot].first.first + 1)
			++l[tot].second;
	sort(l + 1, l + tot + 1, cmp);
	for(int i = 1; i <= tot; ++i)
	{
		r[i] = l[i].first.second;
		f[i] = max(f[i - 1], f[lower_bound(r + 1, r + i + 1, l[i].first.first) - r - 1] + l[i].second);
	}
	printf("%d\n", n - f[tot]);
	return 0;
}
