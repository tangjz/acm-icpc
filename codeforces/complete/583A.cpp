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
const int maxn = 55, mod = 1000000007;
int n, h, v, ans[maxn];
bool r[maxn], c[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n * n; ++i)
	{
		scanf("%d%d", &h, &v);
		if(!r[h] && !c[v])
		{
			r[h] = c[v] = 1;
			ans[h] = i;
		}
	}
	sort(ans + 1, ans + n + 1);
	for(int i = 1; i <= n; ++i)
		printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}
