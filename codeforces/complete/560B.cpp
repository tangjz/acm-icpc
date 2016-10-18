#include <stdio.h>
#include <algorithm>
int a[3], b[3];
bool check()
{
	return std::max(a[1], a[2]) <= a[0] && b[1] + b[2] <= b[0] || a[1] + a[2] <= a[0] && std::max(b[1], b[2]) <= b[0];
}
int main()
{
	for(int i = 0; i < 3; ++i)
		scanf("%d%d", a + i, b + i);
	bool flag = check();
	std::swap(a[1], b[1]);
	flag |= check();
	std::swap(a[2], b[2]);
	flag |= check();
	std::swap(a[1], b[1]);
	flag |= check();
	puts(flag ? "YES" : "NO");
	return 0;
}
