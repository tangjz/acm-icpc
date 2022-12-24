#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, mx, f[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		char typ[3];
		scanf("%s", typ);
		if(typ[0] == 'K') {
			int x;
			scanf("%d", &x);
			int j = lower_bound(f + 1, f + mx + 1, x -= m) - f;
			f[j] = x;
			mx += mx < j;
		} else {
			++m;
			--i;
			--n;
		}
	}
	printf("%d\n", mx + m);
	return 0;
}