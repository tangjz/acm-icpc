#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100000;
int n, a[maxn], r, ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = 31; i >= 0; --i)
	{
		int j;
		for(j = r; j < n; ++j)
			if(a[j] & (1 << i))
				break;
		if(j == n)
			continue;
		swap(a[r], a[j]);
		for(j = 0; j < n; ++j)
			if(j != r && (a[j] & (1 << i)))
				a[j] ^= a[r];
		++r;
	}
	for(int i = 0; i < r; ++i)
		ans ^= a[i];
	printf("%d %d\n", ans, ans ^ a[r - 1]);
	return 0;
}
