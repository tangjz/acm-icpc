#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = (int)8e3 + 1, maxd = 26, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);
int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		static int arr[maxn];
		static bool vis[maxn];
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
			vis[i] = 0;
		}
		for(int i = 1; i + 1 <= n; ++i)
			for(int j = i + 1, sum = arr[i] + arr[j]; j <= n && sum <= n; sum += arr[++j])
				vis[sum] = 1;
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			ans += vis[arr[i]];
		printf("%d\n", ans);
	}
	return 0;
}