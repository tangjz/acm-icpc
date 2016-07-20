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
const int maxn = 110;
int n, m;
bool vis[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	while(n--)
	{
		int s, x;
		scanf("%d", &s);
		while(s--)
		{
			scanf("%d", &x);
			vis[x] = 1;
		}
	}
	for(int i = 1; i <= m; ++i)
		if(!vis[i])
		{
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
