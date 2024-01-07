#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n, a, b, c, d;
		scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
		puts(max((a - b) * n, c - d) <= min((a + b) * n, c + d) ? "Yes" : "No");
	}
	return 0;
}