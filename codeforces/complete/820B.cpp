#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, a;
	scanf("%d%d", &n, &a);
	int m = min(max(n * a / 180, 1), n - 2), dif = n * a - m * 180;
	if(m + 1 <= n - 2 && abs(dif - 180) < abs(dif))
		++m;
	printf("%d %d %d\n", 1, 2, n - m + 1);
	return 0;
}
