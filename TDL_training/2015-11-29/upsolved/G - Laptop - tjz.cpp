#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int t, n, L, R, ans;
pair<int, int> p[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &p[i].first, &p[i].second);
		sort(p, p + n);
		L = R = ans = -1;
		for(int i = 0; i < n; ++i)
			if(p[i].first <= R)
			{
				L = min(L + 1, p[i].first);
				R = min(R + 1, p[i].second);
			}
			else
			{
				L = p[i].first;
				R = p[i].second;
				++ans;
			}
		printf("%d\n", ans);
	}
	return 0;
}
