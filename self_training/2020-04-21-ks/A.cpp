#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int N, B;
		static int A[maxn];
		scanf("%d%d", &N, &B);
		for(int i = 0; i < N; ++i)
			scanf("%d", A + i);
		sort(A, A + N);
		int ans = 0;
		for(int i = 0; i < N; ++i) {
			ans += A[i] <= B;
			B -= A[i];
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}