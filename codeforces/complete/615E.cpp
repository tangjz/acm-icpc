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
const int dx[] = {-1, -2, -1, 1, 2, 1}, dy[] = {2, 0, -2, -2, 0, 2};
const int maxn = 100010, maxs = 1024;
LL n, len, x, y;
int main()
{
	scanf("%I64d", &n);
	if(!n)
	{
		puts("0 0");
		return 0;
	}
	len = sqrt(n / 3);
	while(len * (len + 1) * 3 > n)
		--len;
	while(len * (len + 1) * 3 <= n)
		++len;
	x = (len - 1) * 2, y = 0;
	n -= len * (len - 1) * 3;
	for(int i = 0; i < 6 && n; ++i)
	{
		int tmp = min(n, len);
		if(!i)
		{
			x += dx[5] + dx[i] * (tmp - 1);
			y += dy[5] + dy[i] * (tmp - 1);
		}
		else
		{
			x += dx[i] * tmp;
			y += dy[i] * tmp;
		}
		n -= tmp;
	}
	printf("%I64d %I64d\n", x, y);
	return 0;
}
