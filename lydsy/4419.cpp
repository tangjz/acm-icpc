#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int n, m, a[maxn], b[maxn];
set<int> e[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int x, y;
		char op[2];
		scanf("%s%d", op, &x);
		if(op[0] == '!')
			++a[x];
		else
		{
			scanf("%d", &y);
			if(op[0] == '+')
			{
				e[x].insert(y);
				e[y].insert(x);
				b[x] -= a[y];
				b[y] -= a[x];
			}
			else
			{
				e[x].erase(e[x].find(y));
				e[y].erase(e[y].find(x));
				b[x] += a[y];
				b[y] += a[x];
			}
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		int ret = b[i];
		for(set<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
			ret += a[*it];
		printf("%d%c", ret, " \n"[i == n]);
	}
	return 0;
}
