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
		vector<int> vec;
		for(int pw = 1; n > 0; pw *= 10, n /= 10)
			if(n % 10)
				vec.push_back((n % 10) * pw);
		printf("%d\n", (int)vec.size());
		for(int x : vec)
			printf("%d ", x);
		puts("");
	}
	return 0;
}