#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)1e5 + 1, maxv = (int)1e9;
int t, n;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		if(n & 2) {
			puts("NO");
			continue;
		}
		puts("YES");
		int m = n / 4, dt = maxv / 2;
		for(int i = 0; i < m; ++i) {
			printf("%d %d ", dt + i + i + 2, dt - i - i - 2);
		}
		for(int i = 0; i < m; ++i) {
			printf("%d %d ", dt + i + i + 1, dt - i - i - 1);
		}
		puts("");
	}
	return 0;
}