#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 500010;
int n, a[maxn], ans;
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for(int i = n - 1 >> 1, j = n - 1; i >= 0; --i)
		if((a[i] << 1) <= a[j])
		{
			++ans;
			--j;
			vis[i] = 1;
			while(j > 0 && vis[j])
			    --j;
		}
	printf("%d\n", n - ans);
	return 0;
}
