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
int n, k, f[2333], ans;

int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%d", f + i);
	sort(f + 1, f + n + 1);
	if(n < k) printf("%d\n", (f[n] - 1) << 1);
	else
	{
		for(int i = n; i > 0; i -= k) ans += f[i] - 1;
		printf("%d\n", ans << 1);
	}
	return 0;
}
