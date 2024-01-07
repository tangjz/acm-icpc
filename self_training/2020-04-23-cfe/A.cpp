#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 101, mod = (int)1e9 + 7;
int t, n, p[maxn], c[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", p + i, c + i);
		bool chk = p[0] >= c[0];
		for(int i = 1; chk && i < n; ++i) {
			int dp = p[i] - p[i - 1];
			int dc = c[i] - c[i - 1];
			chk &= dp >= dc && dc >= 0;
		}
		puts(chk ? "YES" : "NO");
	}
	return 0;
}