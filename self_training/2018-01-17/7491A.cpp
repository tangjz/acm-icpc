#include <bits/stdc++.h>
using namespace std;
typedef unsigned UL;
int main() {
	UL mask = 0;
	for(int i = 0; i < 10; ++i) {
		int x;
		scanf("%d", &x);
		mask |= 1UL << (x - 1);
	}
	int n;
	scanf("%d", &n);
	while(n--) {
		int cnt = 0;
		for(int i = 0; i < 6; ++i) {
			int x;
			scanf("%d", &x);
			cnt += (mask >> (x - 1)) & 1;
		}
		puts(cnt >= 3 ? "Lucky" : "Unlucky");
	}
	return 0;
}
