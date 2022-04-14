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
const int maxn = (int)1e5 + 1, maxm = (int)1e6 + 1;

void solve() {
	int n;
	static int arr[3][maxn];
	scanf("%d", &n);
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d", arr[i] + j);
	int fir = arr[0][0], las = fir;
	printf("%d", fir);
	for(int i = 1; i < n; ++i)
		for(int j = 0; j < 3; ++j)
			if(arr[j][i] != las && (i + 1 < n || arr[j][i] != fir)) {
				las = arr[j][i];
				printf(" %d", las);
				break;
			}
	puts("");
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