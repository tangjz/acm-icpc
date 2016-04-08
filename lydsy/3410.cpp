#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50001;
int n, last, ans;
struct Seg
{
	int l, r;
	bool operator < (const Seg &x) const
	{
		return r < x.r;
	}
} p[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &p[i].l, &p[i].r);
	sort(p, p + n);
	for(int i = 0; i < n; ++i)
	{
		if(p[i].l >= last)
		{
			last = p[i].r;
			++ans;
		}
	}
	printf("%d\n", ans);
	return 0;
}
