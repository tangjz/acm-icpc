#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int n, a[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	n = unique(a, a + n + 1) - a - 1;
	printf("%d\n", n);
	return 0;
}
