#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = ~0ULL >> 1;
const int mul[3] = {2, 3, 5};
int cost[5];
unordered_map<LL, LL> Hash;
LL dfs(LL N) {
	auto it = Hash.find(N);
	if(it != Hash.end())
		return it -> second;
	LL ret = INF;
	for(int i = 0; i < 3; ++i) {
		LL M = N / mul[i], R = N % mul[i];
		ret = min(ret, dfs(M) + cost[i] + R * cost[3]);
		if(R > 0 && M + 1 < N)
			ret = min(ret, dfs(M + 1) + cost[i] + (mul[i] - R) * cost[3]);
	}
	if(ret / cost[3] >= N)
		ret = min(ret, N * cost[3]);
	return Hash[N] = ret;
}
int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		LL N;
		scanf("%lld", &N);
		for(int i = 0; i < 4; ++i)
			scanf("%d", cost + i);
		Hash.clear();
		Hash[0] = 0;
		Hash[1] = cost[3];
		printf("%lld\n", dfs(N));
	}
	return 0;
}