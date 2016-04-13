#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 5001;
int n, l[maxn], r[maxn], v[maxn], ord[maxn], match[maxn];
long long ans;
bool fail[maxn];
bool cmp(const int &x, const int &y)
{
	return v[x] > v[y];
}
bool find(int u, int sta)
{
	for(int i = sta; i < r[u]; ++i)
	{
		if(match[i] == -1)
		{
			match[i] = u;
			return 1;
		}
		if(r[u] < r[match[i]] && !fail[match[i]])
		{
			if(find(match[i], i + 1))
			{
				match[i] = u;
				return 1;
			}
			fail[match[i]] = 1;
			return 0;
		}
	}
	return 0;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d%d", l + i, r + i, v + i);
		ord[i] = i;
	}
	sort(ord, ord + n, cmp);
	memset(match, -1, sizeof match);
	for(int i = 0; i < n; ++i)
		if(find(ord[i], l[ord[i]]))
			ans += v[ord[i]];
	printf("%lld\n", ans);
	return 0;
}
