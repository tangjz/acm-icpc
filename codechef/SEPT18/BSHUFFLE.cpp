#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	scanf("%d", &n);
	int m = n >> 1;
	for(int i = 2; i <= m; ++i)
		printf("%d ", i);
	printf("%d ", 1);
	for(int i = m + 2; i <= n; ++i)
		printf("%d ", i);
	printf("%d\n", m + 1);
	printf("%d", n);
	for(int i = 1; i < n; ++i)
		printf(" %d", i);
	putchar('\n');
	return 0;
}
