#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1001, maxh = 1010;
int n, ans = ~0u >> 1;
struct Person
{
	int w, h;
	bool operator < (const Person &x) const
	{
		return w - h > x.w - x.h;
	}
} a[maxn], b[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &a[i].w, &a[i].h);
	for(int i = 1; i < maxh; ++i)
	{
		memcpy(b, a, sizeof a);
		bool flag = 0;
		int cnt = 0;
		for(int j = 0; j < n; ++j)
			if(b[j].h > i)
			{
				if(b[j].w > i)
				{
					flag = 1;
					break;
				}
				else
				{
					swap(b[j].w, b[j].h);
					++cnt;
				}
			}
		if(flag || cnt * 2 > n)
			continue;
		sort(b, b + n);
		for(int j = 0; j < n && (cnt + 1) * 2 <= n; ++j)
			if(b[j].w <= i && b[j].h < b[j].w)
			{
				swap(b[j].w, b[j].h);
				++cnt;
			}
		int tmp = 0;
		for(int j = 0; j < n; ++j)
			tmp += b[j].w;
		if(ans > tmp * i)
			ans = tmp * i;
	}
	printf("%d\n", ans);
	return 0;
}
