#include <cstdio>
#include <algorithm>

using namespace std;

int n, m, k;
int x[10009], l[10000009], r[10000009];
int cc[2000019] , *c = cc + 1000009;
int d[1000009];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", x + i);
	for (int j = 1; j <= m; ++j) {
		scanf("%d%d", l + j, r + j);
		++d[l[j]];
		--d[r[j]];
	}
	int e = 0;
	for (int i = 0; i <= 1000003; ++i) {
		if (e == 0 && e + d[i]) l[k] = i;
		if (e && e + d[i] == 0) r[k++] = i;
		e += d[i];
	}
	for (int j = 0; j < k; ++j) {
		for (int i = 1; i <= n; ++i) {
			++c[l[j] - x[i]];
			--c[r[j] - x[i] + 1];
		}
	}
	int pos = 0x3fffffff;
	int ans = 0, tmp = 0;
	for (int i = -1000003; i <= +1000003; ++i) {
		tmp += c[i];
		if (ans < tmp) {
			ans = tmp;
			pos = abs(i);
		} else if (ans == tmp) {
			if (pos > abs(i))
				pos = abs(i);
		}
	}
	printf("%d %d\n", pos, ans);
	return 0;
}
