#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)5e5 + 1;
const int mod = (int)1e9 + 7;


int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n, ctr[2] = {};
		static int arr[maxn];
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			scanf("%d", arr + i);
			if((arr[i] - i) & 1)
				++ctr[i & 1];
		}
		printf("%d\n", ctr[0] != ctr[1] ? -1 : ctr[0]);
		// printf("Case #%d:");
	}

	return 0;
}