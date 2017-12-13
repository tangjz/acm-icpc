#include <bits/stdc++.h>
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	printf("%d %d\n", m && m < n, std::min(m << 1, n - m));
	return 0;
}
