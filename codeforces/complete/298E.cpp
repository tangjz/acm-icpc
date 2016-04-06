#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 111111;
int n, s[maxn], no[maxn], a[maxn], b[maxn];
bool cmp(const int &x, const int &y)
{
	return s[x] < s[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", s + i);
		no[i] = i;
	}
	sort(no, no + n, cmp);
	for(int i = 0; i < (n + 2) / 3; ++i)
	{
		a[no[i]] = 0;
		b[no[i]] = s[no[i]];
	}
	for(int i = (n + 2) / 3, j = 0; i < n; ++i, ++j)
	{
		a[no[i]] = j >> 1;
		b[no[i]] = s[no[i]] - a[no[i]];
		if(j & 1)
			swap(a[no[i]], b[no[i]]);
	}
	puts("YES");
	for(int i = 0; i < n; ++i)
		printf("%d ", a[i]);
	putchar('\n');
	for(int i = 0; i < n; ++i)
		printf("%d ", b[i]);
	putchar('\n');
	return 0;
}
