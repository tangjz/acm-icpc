#include <bits/stdc++.h>
using namespace std;
int main() {
	const int maxn = (int)1e9 + 1;
	vector<int> dp = vector<int>{0, 2};
	while(dp.back() < maxn) {
		int h = (int)dp.size();
		dp.push_back(dp.back() + 3 * h - 1);
	}
	dp.pop_back();
	reverse(dp.begin(), dp.end());
	dp.pop_back();
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int cnt = 0;
		for(int x : dp)
			if(n >= x) {
				cnt += n / x;
				n %= x;
			}
		printf("%d\n", cnt);
	}
	return 0;
}