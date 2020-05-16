#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1;
int n;
LL sx, sy;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n + n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		sx += x;
		sy += y;
	}
	printf("%d %d\n", (int)(sx / n), (int)(sy / n));
	return 0;
}