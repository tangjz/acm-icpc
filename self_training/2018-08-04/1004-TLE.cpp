#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e3 + 1;
int t, n, ord[maxn << 1 | 1], ans;
char out[maxn];
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	int det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	int site() const {
		return x < 0 || (!x && y < 0);
	}
	bool operator < (Point const &t) const {
		int s1 = site(), s2 = t.site();
		if(s1 != s2)
			return s1 < s2;
		return det(t) > 0;
	}
} a[maxn], b[maxn];
bool cmp(int const &u, int const &v) {
	return b[u] < b[v];
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		n <<= 1;
		ans = 0;
		for(int i = 0; i < n; ++i) {
			a[i].read();
			out[i] = 'B';
		}
		out[n] = '\0';
		for(int i = 0; i < n; ++i) {
			int tot = 0;
			for(int j = 0; j < n; ++j) {
				if(i == j)
					continue;
				b[j] = a[j] - a[i];
				ord[tot++] = j;
			}
			sort(ord, ord + tot, cmp);
			for(int j = 0; j < tot; ++j)
				ord[tot + j] = ord[j];
			for(int j = 0, k = 0; j < tot; ++j) {
				for( ; k < tot + j && b[ord[j]].det(b[ord[k]]) >= 0; ++k);
				if(k - j == (n >> 1) && ord[j] < i) {
					ans += 2;
					static char tmp[maxn];
					for(int x = 0; x < n; ++x)
						tmp[x] = 'B';
					for(int x = j; x < k; ++x)
						tmp[ord[x]] = 'A';
					tmp[n] = '\0';
					if(strcmp(out, tmp) > 0)
						strcpy(out, tmp);
				}
			}
		}
		printf("Case #%d: %d %s\n", Case, ans, out);
	}
	return 0;
}
