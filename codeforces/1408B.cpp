#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;
const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)1e2 + 1, maxm = (int)1e6 + 1;

void solve() {
	int n, m;
	static int a[maxn];
	scanf("%d%d", &n, &m);
	int cnt = 0;
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		if(!i || a[i - 1] < a[i])
			++cnt;
	}
	if(cnt == 1) {
		puts("1");
	} else if(m == 1) {
		puts("-1");
	} else {
		printf("%d\n", (cnt - 2) / (m - 1) + 1);
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