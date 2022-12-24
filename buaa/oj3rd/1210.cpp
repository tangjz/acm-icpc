#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000010;
set<int> s;
int n, a[maxn], ans[maxn];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		s.clear();
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = n - 1; i >= 0; --i)
		{
			set<int>::iterator it = s.upper_bound(a[i]);
			if(it == s.end())
				ans[i] = -1;
			else
				ans[i] = *it;
			s.insert(a[i]);
		}
		for(int i = 0; i < n; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
