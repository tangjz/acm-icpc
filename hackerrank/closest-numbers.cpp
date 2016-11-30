#include <stdio.h>
#include <algorithm>
const int maxn = 200001;
int n, a[maxn], pos;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	std::sort(a, a + n);
	for(int i = 1; i + 1 < n; ++i)
		if(a[pos + 1] - a[pos] > a[i + 1] - a[i])
			pos = i;
	for(int i = 0; i + 1 < n; ++i)
		if(a[pos + 1] - a[pos] == a[i + 1] - a[i])
			printf("%d %d ", a[i], a[i + 1]);
	putchar('\n');
	return 0;
}
