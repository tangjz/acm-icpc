#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	printf("%d\n", max(n - (m - n - n), 0));
	return 0;
}