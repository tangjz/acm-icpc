#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
#define x first
#define y second
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7;

int main() {
	int t = 1;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int n;
		static bool vis[maxn];
		scanf("%d", &n);
		memset(vis, 0, n * sizeof(bool));
		for(int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			(x %= n) < 0 && (x += n);
			(x += i) >= n && (x -= n);
			vis[x] = 1;
		}
		int pos;
		for(pos = 0; pos < n && vis[pos]; ++pos);
		puts(pos < n ? "NO" : "YES");
	}
	return 0;
}