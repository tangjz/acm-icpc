#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e4 + 1;
int t, n, x[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int sum = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%d", x + i);
			sum ^= x[i];
		}
		if(!sum) {
			puts("Draw");
			continue;
		}
		if(!(n & 1)) {
			puts("Alice");
			continue;
		}
		int cnt = 0;
		for(int i = 30; i >= 0; --i)
			if((sum >> i) & 1) {
				for(int j = 0; j < n; ++j) {
					x[j] = (x[j] >> i) & 1;
					cnt += x[j];
				}
				break;
			}
		bool chk = 0;
		if(!(cnt & 2)) {
			if(x[0]) {
				int L = 1, R = n - 1;
				for( ; L < R && x[L] == x[R]; ++L, --R);
				chk = 1;
				for( ; chk && L < R; L += 2)
					chk &= x[L] == x[L + 1];
			}
			if(!chk && x[n - 1]) {
				int L = 0, R = n - 2;
				for( ; L < R && x[L] == x[R]; ++L, --R);
				chk = 1;
				for( ; chk && L < R; L += 2)
					chk &= x[L] == x[L + 1];
			}
		}
		puts(chk ? "Alice" : "Bob");
	}
	return 0;
}
