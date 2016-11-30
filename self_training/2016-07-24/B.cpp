#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 100001;
int n, m, q, a[maxn], ans;
int main()
{
	scanf("%d", &m);
	q = maxn;
	while(m--)
	{
		int x;
		scanf("%d", &x);
		if(x < q)
			q = x;
	}
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n, greater<int>());
	for(int i = 0; i < n; i += q + 2)
		for(int j = 0; j < q && i + j < n; ++j)
			ans += a[i + j];
	printf("%d\n", ans);
	return 0;
}
