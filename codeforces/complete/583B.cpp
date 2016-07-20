#include <set>
#include <map>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 1010, mod = 1000000007;
int n, a[maxn], cnt, ans;
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 0; i < n; ++i)
	{
		if(i & 1)
		{
			for(int j = n; j; --j)
				if(!vis[j] && a[j] <= cnt)
				{
					vis[j] = 1;
					++cnt;
				}
		}
		else
		{
			for(int j = 1; j <= n; ++j)
				if(!vis[j] && a[j] <= cnt)
				{
					vis[j] = 1;
					++cnt;
				}
		}
		if(cnt == n)
		{
			ans = i;
			break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
