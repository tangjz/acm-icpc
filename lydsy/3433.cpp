#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 151;
int n, last[2], ans;
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
		if(p[i].l >= last[0])
		{
			last[0] = p[i].r;
			++ans;
		}
		else if(p[i].l >= last[1])
		{
			last[1] = p[i].r;
			++ans;
		}
		if(last[0] < last[1])
			swap(last[0], last[1]);
	}
	printf("%d\n", ans);
	return 0;
}
