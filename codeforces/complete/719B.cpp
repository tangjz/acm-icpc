#include <stdio.h>
#include <algorithm>
const int maxn = 100001;
int n, c[2][2];
char str[maxn];
int main()
{
	scanf("%d%s", &n, str);
	for(int i = 0; i < n; ++i)
		++c[i & 1][str[i] == 'r'];
	printf("%d\n", std::min(std::max(c[0][0], c[1][1]), std::max(c[0][1], c[1][0])));
	return 0;
}
