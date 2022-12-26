#include <bits/stdc++.h>
using namespace std;
int t, n, m, x, y;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d", &n, &m, &x, &y);
		puts(((n - 1) % x == 0 && (m - 1) % y == 0) || (n > 1 && (n - 2) % x == 0 && m > 1 && (m - 2) % y == 0) ? "Chefirnemo" : "Pofik");
	}
	return 0;
}
