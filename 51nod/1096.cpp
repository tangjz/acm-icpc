#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10010;
int n, p[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", p + i);
	sort(p, p + n);
	int x = p[n >> 1];
	long long ret = 0;
	for(int i = 0; i < n; ++i)
		ret += abs(p[i] - x);
	printf("%lld\n", ret);
	return 0;
} 
