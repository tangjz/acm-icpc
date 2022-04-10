#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int t, n;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", (n - 1) >> 1);
	}
	return 0;
}