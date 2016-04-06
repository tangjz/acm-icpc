#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int n, a[3333], ans[3333][2], tot;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = 0; i < n; ++i)
	{
		int tmp = i;
		for(int j = i + 1; j < n; ++j)
			if(a[j] < a[tmp])
				tmp = j;
		if(tmp != i)
		{
			ans[tot][0] = i;
			ans[tot][1] = tmp;
			++tot;
			int t = a[i];
			a[i] = a[tmp];
			a[tmp] = t;
		}
	}
	printf("%d\n", tot);
	for(int i = 0; i < tot; ++i)
	{
		printf("%d %d\n", ans[i][0], ans[i][1]);
	}
	return 0;
}
