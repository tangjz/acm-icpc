#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
int n, ans;
LL x1, y1, x2, y2;
LL val(LL a, LL b, LL c, LL x, LL y)
{
	return a * x + b * y + c;
}
int main()
{
	scanf("%I64d%I64d%I64d%I64d", &x1, &y1, &x2, &y2);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		LL a, b, c;
		scanf("%I64d%I64d%I64d", &a, &b, &c);
		LL ret1 = val(a, b, c, x1, y1), ret2 = val(a, b, c, x2, y2);
		if(ret1 < 0 && ret2 > 0 || ret1 > 0 && ret2 < 0)
			++ans;
	}
	printf("%d\n", ans);
	return 0;
}
