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
const int maxn = (int)2e3 + 1, maxm = (int)1e6 + 9;

void solve() {
	int n, m;
	static pair<int, int> a[maxn], b[maxn];
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &a[i].first, &a[i].second);
	for(int i = 0; i < m; ++i)
		scanf("%d%d", &b[i].first, &b[i].second);
	int mx = 1;
	static int upp[maxm];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(a[i].first <= b[j].first && a[i].second <= b[j].second) {
				int dx = b[j].first - a[i].first;
				int dy = b[j].second - a[i].second;
				for( ; mx <= dx; upp[mx++] = 0);
				upp[dx] = max(upp[dx], dy + 1);
			}
	int ans = maxm << 1;
	upp[mx] = 0;
	for(int i = mx; i >= 0; --i) {
		ans = min(ans, i + upp[i]);
		if(i > 0)
			upp[i - 1] = max(upp[i - 1], upp[i]);
	}
	printf("%d\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}