#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
typedef long double LDB;
const int maxn = 100010, maxm = 200010;
int n, m, deg[maxn], f[maxn];
LL ans;
vector<int> e[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(u > v)
			swap(u, v);
		e[v].push_back(u);
		++deg[u];
		++deg[v];
	}
	for(int i = 1; i <= n; ++i)
	{
		for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
			f[i] = max(f[i], f[*it]);
		++f[i];
		ans = max(ans, (LL)f[i] * deg[i]);
	}
	printf("%I64d\n", ans);
	return 0;
}
