#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, m, k, a[maxn], b[maxn];
bool flag = 0;
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for(int i = 0; i < m; ++i)
		scanf("%d", b + i);
	sort(b, b + m);
	for(int i = n - 1, j = m - 1; i >= 0 && j >= 0; --i, --j)
		if(a[i] > b[j])
		{
			flag = 1;
			break;
		}
		else if(i && !j)
		{
			flag = 1;
			break;
		}
		else if(!i)
			break;
	puts(flag ? "YES" : "NO");
	return 0;
}
