#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;
int n, m, a[maxn], b[maxn];
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i) {
			scanf("%d", a + i);
			b[i] = 0;
		}
		for(int i = 1; i + 1 < n; ++i)
			b[i] = a[i] > a[i - 1] && a[i] > a[i + 1];
		for(int i = 1; i < n; ++i)
			b[i] += b[i - 1];
		int ans = -1, pos = -1;
		for(int i = 0; i + m <= n; ++i) {
			int tmp = b[i + m - 2] - b[i];
			if(ans < tmp) {
				ans = tmp;
				pos = i;
			}
		}
		printf("%d %d\n", ans + 1, pos + 1);
	}
	return 0;
}