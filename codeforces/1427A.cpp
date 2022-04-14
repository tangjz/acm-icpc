#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)3e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

bool check(int n, int arr[]) {
	int sum = 0;
	for(int i = 0; i < n; ++i) {
		sum += arr[i];
		if(!sum)
			return 0;
	}
	return 1;
}

void solve() {
	int n;
	static int a[maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	if(!check(n, a))
		reverse(a, a + n);
	if(!check(n, a)) {
		puts("NO");
	} else {
		puts("YES");
		for(int i = 0; i < n; ++i)
			printf("%d%c", a[i], " \n"[i == n - 1]);
	}
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}