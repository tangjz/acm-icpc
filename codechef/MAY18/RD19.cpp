#include <bits/stdc++.h>
using namespace std;
const int maxn = 1001;
int t, n, r;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		r = 0;
		while(n--) {
			int x;
			scanf("%d", &x);
			r = __gcd(r, x);
		}
		puts(r == 1 ? "0" : "-1");
	}
	return 0;
}
