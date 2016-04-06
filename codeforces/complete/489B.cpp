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
int n, m, a[233], b[233], f[233][233];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d", b + i);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			f[i][j] = max(f[i][j - 1], f[i - 1][j]);
			if(abs(a[i] - b[j]) <= 1)
				f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
		}
	printf("%d\n", f[n][m]);
	return 0;
}
