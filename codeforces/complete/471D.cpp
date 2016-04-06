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
int n, m, a[200010], b[200010], f[200010], ans;
int main()
{
	scanf("%d%d", &n, &m);
	if(m == 1)
	{
		printf("%d\n", n);
		return 0;
	}
	for(int i = 0; i < n; ++i) scanf("%d", a + i);
	for(int i = --n; i; --i) a[i] -= a[i - 1]; a[0] = 0;
	for(int i = 0; i < m; ++i) scanf("%d", b + i);
	for(int i = --m; i; --i) b[i] -= b[i - 1]; b[0] = 0;
	for(int i = 2, j = 0; i <= m; ++i)
	{
		while(j && b[i] != b[j + 1]) j = f[j];
		if(b[i] == b[j + 1]) ++j;
		f[i] = j;
	}
	for(int i = 1, j = 0; i <= n; ++i)
	{
		while(j && a[i] != b[j + 1]) j = f[j];
		if(a[i] == b[j + 1]) ++j;
		if(j == m)
		{
			++ans;
			j = f[j];
		}
	}
	printf("%d\n", ans);
	return 0;
}
