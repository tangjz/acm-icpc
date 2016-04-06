#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
long long n, h, ans;

int main()
{
	scanf("%I64d", &n);
	for(h = 1; (h + 1) * h / 2 * 3 <= h + n; ++h)
		if((h + n) % 3 == 0) ++ans;
	printf("%I64d\n", ans);
	return 0;
}

