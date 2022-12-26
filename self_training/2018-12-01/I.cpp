#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		static char buf[maxn];
		scanf("%s", buf);
		int c[3] = {};
		for(int i = 0; buf[i]; ++i)
			++c[buf[i] - '0'];
		int mx = max(c[0], max(c[1], c[2])), sum = c[0] + c[1] + c[2];
		if(mx > sum - mx + 1) {
			puts("-1");
		} else {
			int pos = -1, op[3] = {}, rem[3] = {c[0] - 1, c[1] - 1, c[2] - 1};
			if(mx == sum - mx + 1 && mx >= 2)
				if(mx == c[0]) { // c[1] + c[2]
					pos = 0;
					--rem[0];
				} else if(mx == c[1] && c[2]) {
					pos = 1;
					--rem[1];
				}
			while(rem[0] > 0 || rem[1] > 0 || rem[2] > 0) {
				int low = min(rem[0], min(rem[1], rem[2]));
				int i = low == rem[2] ? 2 : (low == rem[0] ? 0 : 1);
				int j = !i, k = 3 - i - j;
				++op[i];
				--rem[j];
				--rem[k];
			}
			printf("%d\n", op[0] + op[1] + op[2] + (pos >= 0));
			for(int i = 0; i < op[0]; ++i) {
				int x = c[0] + c[1];
				printf("%d %d\n", x, x + 1);
				--c[1];
				--c[2];
			}
			if(pos == 1) {
				int x = c[0] + c[1];
				printf("%d %d\n", x, x);
				--c[1];
			}
			for(int i = 0; i < op[2]; ++i) {
				int x = c[0];
				printf("%d %d\n", x, x + 1);
				--c[0];
				--c[1];
			}
			assert(c[1] <= 1);
			for(int i = 0; i < op[1]; ++i) {
				int x = c[0], y = c[0] + c[1];
				printf("%d %d\n", x, y + 1);
				--c[0];
				c[1] = 0;
				--c[2];
			}
			if(!pos) {
				int x = c[0];
				printf("%d %d\n", x, x);
				--c[0];
			}
		}
	}
	return 0;
}