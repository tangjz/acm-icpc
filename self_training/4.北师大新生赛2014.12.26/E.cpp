#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct Line
{
	int l, r;
	bool operator < (const Line &x) const { return r < x.r; }
} line[233333];
int t, n;
int r[233333], f[233333];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(f, 0, sizeof f);
		memset(r, 0, sizeof r);
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", &line[i].l, &line[i].r);
		sort(line + 1, line + n + 1);
		for(int i = 1; i <= n; ++i)
		{
			r[i] = line[i].r;
			f[i] = max(f[i - 1], f[upper_bound(r + 1, r + i, line[i].l - 1) - r - 1] + 1);
		}
		printf("%d\n", f[n]);
	}
	return 0;
}
