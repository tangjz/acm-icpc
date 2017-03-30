#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxs = 100001;
char a[maxs], b[maxs];
int main()
{
	scanf("%s%s", a, b);
	printf("%d\n", strcmp(a, b) ? std::max(strlen(a), strlen(b)) : -1);
	return 0;
}
