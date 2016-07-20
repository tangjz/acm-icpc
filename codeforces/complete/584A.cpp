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
const int maxn = 100010, mod = 1000000007;
int n, m, ans;
int main()
{
	scanf("%d%d", &n, &m);
	if(m == 10)
	{
		if(n == 1)
			puts("-1");
		else
		{
			putchar('1');
			for(int i = 1; i < n; ++i)
				putchar('0');
		}
		return 0;
	}
	if(n == 1)
	{
		printf("%d\n", m);
		return 0;
	}
	ans = 1;
	putchar('1');
	for(int i = 2; i < n; ++i)
	{
		ans = ans * 10 % m;
		putchar('0');
	}
	ans = ans * 10 % m;
	printf("%d\n", m - ans);
	return 0;
}
