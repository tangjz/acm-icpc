#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 51;
int n;
LL a[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%lld", a + i);
	for(int i = 0, k; i < n; ++i)
	{
		for(int j = i + 1; j < n; ++j)
			if(a[i] < a[j])
				swap(a[i], a[j]);
		if(!a[i])
			break;
		for(k = 60; ~(a[i] >> k) & 1; --k);
		for(int j = 0; j < n; ++j)
			if(i != j && ((a[j] >> k) & 1))
				a[j] ^= a[i];
	}
	for(int i = 1; i < n; ++i)
		a[0] ^= a[i];
	for(int i = 1; i < n; ++i)
		a[i] ^= a[0];
	for(int i = 0; i < n; ++i)
		ans += a[i];
	printf("%lld\n", ans);
	return 0;
}
