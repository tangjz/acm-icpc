#include <bits/stdc++.h>
using namespace std;
int t, n, m, q, dt;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &dt, &q);
		++dt;
		while(q--) {
			scanf("%d", &m);int tp = m;
			--m;
			int idx = 0;
			while(m) {
				if(m >= dt) {
					int k = m / dt;
					idx += k;
					m -= k * dt;
				}
				if(m) {
					++idx;
					(m = (m - dt) % (n - idx)) < 0 && (m += n - idx);
				}
			}
			printf("%d\n", idx + 1);
		}
	}
	return 0;
}
