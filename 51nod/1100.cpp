#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 10001;
int n, x[maxn], y[maxn], ord[maxn], pos;
bool cmp(int const &u, int const &v) {
	return x[u] < x[v];
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", x + i, y + i);
		ord[i] = i;
	}
	std::sort(ord, ord + n, cmp);
	for(int i = 1; i + 1 < n; ++i)
		if((LL)(y[ord[pos + 1]] - y[ord[pos]]) * (x[ord[i + 1]] - x[ord[i]]) < (LL)(y[ord[i + 1]] - y[ord[i]]) * (x[ord[pos + 1]] - x[ord[pos]]))
			pos = i;
	printf("%d %d\n", ord[pos] + 1, ord[pos + 1] + 1);
	return 0;
}
