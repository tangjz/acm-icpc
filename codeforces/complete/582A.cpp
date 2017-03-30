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
const int maxn = 510, mod = 1000000007;
int n, tot, a[maxn];
map<int, int, greater<int> > Hash;
int main()
{
	scanf("%d", &n);
	for(int i = 1, x; i <= n * n; ++i)
	{
		scanf("%d", &x);
		++Hash[x];
	}
	while(tot < n)
	{
		map<int, int>::iterator it = Hash.begin();
		--Hash[it -> first];
		if(!Hash[it -> first])
			Hash.erase(it -> first);
		for(int i = 0; i < tot; ++i)
		{
			int r = __gcd(a[i], it -> first);
			Hash[r] -= 2;
			if(!Hash[r])
				Hash.erase(r);
		}
		a[tot++] = it -> first;
	}
	for(int i = 0; i < tot; ++i)
		printf("%d%c", a[i], " \n"[i == tot - 1]);
	return 0;
}
