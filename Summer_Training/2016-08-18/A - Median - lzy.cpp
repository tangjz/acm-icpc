#include <cstdio>
#include <algorithm>

using namespace std;

int T, n, m, tot, s1, s2, l1, r1, l2, r2;
int a[100009];

int get(int k) {
	//printf("k: %d\n", k);
	if (r1 < l2) {
		if (k <= s1) return a[l1 + k - 1];
		else return a[l2 + k - s1 - 1];
	} else {
		int l = min(l1 ,l2), r = max(r1, r2), m, s, t;
		while (l < r) {
			m = (l + r) >> 1;
			s = 0;
			if (m >= l1) s += min(m, r1) - l1 + 1;
			if (m >= l2) s += min(m, r2) - l2 + 1;
			t = s;
			if (l1 <= m && m <= r1 && l2 <= m && m <= r2) --s;
			if (s == k || t == k) {
				l = r = m;
				break;
			}
			if (s > k) r = m - 1;
			if (t < k) l = m + 1;
		}
		return a[l];
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		while (m--) {
			scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
			if (l1 > l2) {
				swap(l1, l2);
				swap(r1, r2);
			}
			s1 = r1 - l1 + 1;
			s2 = r2 - l2 + 1;
			tot = s1 + s2;
			if (tot & 1) printf("%.1f\n", (double)get((tot + 1) / 2));
			else printf("%.1f\n", get(tot / 2) * .5 + get(tot / 2 + 1) * .5 + 1e-6);
		}
	}
	return 0;
}
