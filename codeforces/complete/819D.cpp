#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int t, n, tim[maxn], ord[maxn], ans[maxn];
int exgcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
int main() {
	scanf("%d%d", &t, &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", tim + i);
		tim[i] = (tim[i - 1] + tim[i]) % t;
	}
	int x, y, r = exgcd(tim[n], t, x, y);
	t /= r;
	x < 0 && (x += t);
	for(int i = 1; i <= n; ++i) {
		ord[i] = i;
		ans[i] = tim[i] % r;
	}
	sort(ord + 1, ord + n + 1, [&](int const &x, int const &y) {
		return ans[x] < ans[y];
	});
	for(int i = 1, j = 1; i <= n; i = j) {
		int cpos = ans[ord[i]];
		for( ; j <= n && cpos == ans[ord[j]]; ++j) {
			int o = ord[j];
			tim[o] = (tim[o] - cpos) / r * (long long)x % t; // orbit position
		}
		sort(ord + i, ord + j, [&](int const &x, int const &y) {
			return tim[x] < tim[y] || (tim[x] == tim[y] && x > y);
		});
		for(int k = i; k + 1 < j; ++k)
			ans[ord[k]] = tim[ord[k + 1]] - tim[ord[k]]; // k -> k + 1
		ans[ord[j - 1]] = tim[ord[i]] + t - tim[ord[j - 1]];
	}
	for(int i = 1; i <= n; ++i)
		printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}
