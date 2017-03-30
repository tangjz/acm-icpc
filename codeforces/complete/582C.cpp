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
const int maxn = 200010, mod = 1000000007;
int n, a[maxn << 1], mx[maxn];
bool used[maxn << 1];
LL ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		a[n + i] = a[i];
	}
	for(int sz = 1; sz < n; ++sz)
	{
		if(n % sz != 0)
			continue;
		memset(mx, 0, sz * sizeof(int));
		for(int i = 0; i < n; ++i)
			mx[i % sz] = max(mx[i % sz], a[i]);
		for(int i = 0; i < n << 1; ++i)
			used[i] = mx[i % sz] == a[i];
		for(int i = 0, j = 0; i <= n << 1; ++i)
			if(used[i])
				++j;
			else
			{
				if(i - j >= n)
					break;
				for(int k = sz; k <= j && k < n; k += sz)
					if(__gcd(k, n) == sz)
						ans += min(j - k + 1, n - i + j);
				j = 0;
			}
	}
	printf("%I64d\n", ans);
	return 0;
}
