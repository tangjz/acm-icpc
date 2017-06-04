#include <map>
#include <cstdio>
#include <algorithm>
const int maxn = 1001, maxm = 11;
int n, m;
std::map<std::pair<int, int>, int> Hash[maxm];
int dfs(int dep, int pre, int sum) {
	std::pair<int, int> state = std::make_pair(pre, sum);
	if(Hash[dep].count(state))
		return Hash[dep][state];
	int ret = 0;
	if(dep >= m - 1) {
		if((sum << 1) + 1 >= n)
			ret += (sum + 1) - std::max(pre + 1, n - sum) + 1;
		return Hash[dep][state] = ret;
	}
	for(int cur = sum + 1; cur > pre; --cur) {
		int tmp = dfs(dep + 1, cur, sum + cur);
		if(!tmp)
			break;
		ret += tmp;
	}
	return Hash[dep][state] = ret;
}
int main() {
	scanf("%d", &n);
	for(m = 1; (1 << m) <= n; ++m);
	printf("%d %d\n", m, dfs(1, 1, 1));
	return 0;
}
