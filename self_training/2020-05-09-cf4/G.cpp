#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);
int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		scanf("%d", &n);
		if(n <= 3) {
			puts("-1");
			continue;
		}
		int tot = 0, pos;
		static int arr[maxn];
		for(int i = 1; i <= n; i += 2)
			arr[tot++] = i;
		pos = arr[tot - 1] == n ? tot - 1 : tot;
		for(int i = n - (n & 1); i > 0; i -= 2)
			arr[tot++] = i;
		if(n & 1) {
			swap(arr[pos + 1], arr[pos + 2]);
		} else {
			swap(arr[pos - 1], arr[pos - 2]);
		}
		for(int i = 0; i < tot; ++i)
			printf("%d%c", arr[i], " \n"[i == tot - 1]);
	}
	return 0;
}