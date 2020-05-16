#include <map>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std;
long long x, y, m;
int main()
{
	long long ans = 0, tot;
	scanf("%I64d%I64d%I64d", &x, &y, &m);
	if(x >= m || y >= m) { printf("0\n"); return 0; }
	if(x <= 0 && y <= 0) { printf("-1\n"); return 0; }
	if(x > y) swap(x, y);
	while(y < m)
	{
		tot = (y - x) / y + 1;
		ans += tot;
		x += tot * y;
		swap(x, y);
	}
	printf("%I64d\n", ans);
	return 0;
}
