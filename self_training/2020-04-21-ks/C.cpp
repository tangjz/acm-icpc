#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int N, K;
		static int A[maxn];
		scanf("%d%d", &N, &K);
		for(int i = 0; i < N; ++i)
			scanf("%d", A + i);
		int L = 1, R = 1;
		for(int i = N - 1; i > 0; --i) {
			A[i] -= A[i - 1];
			R = max(R, A[i]);
		}
		while(L < R) {
			int M = (L + R) >> 1, cnt = 0;
			for(int i = 1; i < N; ++i)
				cnt += A[i] / M + (A[i] % M > 0) - 1;
			if(cnt <= K) {
				R = M;
			} else {
				L = M + 1;
			}
		}
		printf("Case #%d: %d\n", Case, R);
	}
	return 0;
}