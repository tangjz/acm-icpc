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
		for(int i = 2, j; (j = (1 << i) - 1) <= n; ++i)
			if(n % j == 0) {
				printf("%d\n", n / j);
				break;
			}
	}
	return 0;
}