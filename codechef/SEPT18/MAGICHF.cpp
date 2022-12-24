#include <bits/stdc++.h>
using namespace std;
int t, n, m, x, y, z;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &x, &m);
		while(m--) {
			scanf("%d%d", &y, &z);
			if(x == y) {
				x = z;
			} else if(x == z) {
				x = y;
			}
		}
		printf("%d\n", x);
	}
	return 0;
}
