#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int t, n, m, a[maxn], b[maxn], ord[maxn];
set<int> pos[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i <= n; ++i)
			pos[i].clear();
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", b + i);
			pos[b[i]].insert(i);
		}
		bool flag = 1;
		for(int i = 1; i <= n; ++i)
		{
			if(!pos[a[i]].size())
			{
				flag = 0;
				break;
			}
			ord[i] = *pos[a[i]].begin();
			pos[a[i]].erase(ord[i]);
		}
		while(m--)
		{
			int l, r;
			scanf("%d%d", &l, &r);
			if(flag)
				std::sort(ord + l, ord + r + 1);
		}
		for(int i = 1; i <= n && flag; ++i)
			flag &= ord[i] == i;
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
