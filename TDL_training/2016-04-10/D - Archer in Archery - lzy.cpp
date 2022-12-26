#include <cstdio>
#include <algorithm>

using std::sort;

#define N 10000

int T, n, o[N + 9], h[N + 9], s[N + 9], t[N + 9];

bool cmp(int a, int b) {
	return t[a] > t[b];
}

bool check(int m) {
	for (int i = 0; i < n; ++i) {
		o[i] = i;
		if (m < h[i]) return false;

		t[i] = (m - h[i]) / s[i];

	}
	sort(o, o + n, cmp);
	int p = t[o[0]] + 1;
	if (p < 0) return false;
	//printf("\n%d --------\n", m);
	for (int ii = 0; ii < n; ++ii) {;
		int i = o[ii];
		//printf("%d ", t[i]);
		if (t[i] < p) p = t[i];
		else --p;
		//printf("%d\n", p);
		if (p < 0) return false;
	}
	return true;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		int l = 0, r = 100000000, m;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", h + i);
			if (l < h[i]) l = h[i];
		}
		for (int i = 0; i < n; ++i) scanf("%d", s + i);
		while (l < r) {
			m = (l + r) >> 1;
			if (check(m)) r = m;
			else l = m + 1;
		}
		printf("%d\n", l);
	}
	return 0;
}
