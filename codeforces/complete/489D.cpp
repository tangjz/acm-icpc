#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
map<int, int> g1[3010];
int g2[3010];
long long ans;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1, u ,v; i <= m; ++i)
	{
		scanf("%d%d", &u, &v);
		++g1[u][v];
	}
	for(int i = 1; i <= n; ++i)
	{
		memset(g2, 0, sizeof g2);
		for(map<int, int>::iterator it1 = g1[i].begin(), jt1 = g1[i].end(); it1 != jt1; ++it1)
		{
			int j = it1 -> first;
			for(map<int, int>::iterator it2 = g1[j].begin(), jt2 = g1[j].end(); it2 != jt2; ++it2)
			{
				int k = it2 -> first;
				g2[k] += (it1 -> second) * (it2 -> second);
			}
		}
		for(int j = 1; j <= n; ++j)
			if(i != j && g2[j] >= 2)
				ans += (long long)g2[j] * (g2[j] - 1) / 2;
	}
	printf("%I64d\n", ans);
	return 0;
}
