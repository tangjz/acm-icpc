#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		if(!n) {
			puts("1 1");
			continue;
		}
		bool chk = 0;
		for(int i = 1; i * i < n; ++i)
			if(n % i == 0 && (i & 1) == ((n / i) & 1)) {
				int x = (n / i + i) >> 1, y = (n / i - i) >> 1, z = x / (y + 1) + 1;
				if(x / z == y) {
					chk = 1;
					printf("%d %d\n", x, z);
					break;
				}
			}
		if(!chk)
			puts("-1");
	}
	return 0;
}
