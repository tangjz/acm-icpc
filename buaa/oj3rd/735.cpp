#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000010;
int t, n, m, que[maxn], l, r, ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		l = r = ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", que + (r++));
			while(que[r - 1] - que[l] + 1 > m + r - l)
				++l;
			if(ans < m + r - l)
				ans = m + r - l;
		}
		printf("%d\n", ans);
	}
	return 0;
}
