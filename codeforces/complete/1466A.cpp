#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;
 
const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)1e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);
 
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
 
void solve() {
	int n;
	static int a[maxn];
	unordered_set<int> Hash;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		for(int j = 0; j < i; ++j)
			Hash.insert(a[i] - a[j]);
	}
	printf("%d\n", (int)Hash.size());
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