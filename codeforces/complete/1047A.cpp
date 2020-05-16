#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
	scanf("%d", &n);
	int rem = (n - 3) % 3, a[3] = {1, 1, n - 2 - rem};
	for( ; rem--; ++a[rem]);
	printf("%d %d %d\n", a[0], a[1], a[2]);
	return 0;
}
