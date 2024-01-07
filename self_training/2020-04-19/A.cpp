#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int N;
		static int H[maxn];
		scanf("%d", &N);
		for(int i = 1; i <= N; ++i)
			scanf("%d", H + i);
		int ans = 0;
		for(int i = 2; i < N; ++i)
			ans += H[i - 1] < H[i] && H[i] > H[i + 1];
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}