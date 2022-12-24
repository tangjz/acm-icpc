#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int n, a[maxn], b[maxn];
bool cmp(const int &x, const int &y)
{
	return a[x] < a[y] || a[x] == a[y] && x < y;
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", a + i);
			b[i] = i;
		}
		sort(b, b + n, cmp);
		for(int i = 0; i < n; ++i)
			printf("%d%c", b[i] + 1, " \n"[i == n - 1]);
	}
	return 0;
}
