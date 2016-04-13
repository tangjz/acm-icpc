#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 5001;
int n, l[maxn], r[maxn], v[maxn], ord[maxn], b[maxn], match[maxn];
bool fail[maxn];
long long ans;
bool cmp1(const int &x, const int &y)
{
	return l[x] < l[y];
}
bool cmp2(const int &x, const int &y)
{
	return v[x] > v[y];
}
bool find(int u, int sta)
{
	for(int i = sta; b[i] <= r[u]; ++i)
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
	sort(ord, ord + n, cmp1);
	b[0] = l[ord[0]];
	for(int i = 1; i < n; ++i)
		b[i] = max(b[i - 1] + 1, l[ord[i]]);
	b[n] = 0x3f3f3f3f;
	sort(ord, ord + n, cmp2);
	memset(match, -1, n * sizeof(int));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(l[ord[i]] <= b[j] && b[j] <= r[ord[i]])
			{
				if(find(ord[i], j))
					ans += v[ord[i]];
				break;
			}
	printf("%lld\n", ans);
	return 0;
}
