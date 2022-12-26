#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1001;
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int N;
		LL D;
		static LL X[maxn];
		scanf("%d%lld", &N, &D);
		for(int i = 1; i <= N; ++i)
			scanf("%lld", X + i);
		LL ans = D;
		for(int i = N; i >= 1; --i)
			ans = ans / X[i] * X[i];
		printf("Case #%d: %lld\n", Case, ans);
	}
	return 0;
}