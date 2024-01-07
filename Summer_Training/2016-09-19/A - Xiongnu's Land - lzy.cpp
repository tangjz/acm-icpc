#include <cstdio>
#include <algorithm>

using namespace std;

#define N 10000

typedef long long i64;
struct Rect {int x, len;};

int T, R, n, m, x, y, w, h, cur;
i64 sum, all, now;
Rect r[2 * N + 9];

bool cmp(const Rect &a, const Rect &b) {
	return a.x < b.x;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &R);
		scanf("%d", &n);
		m = 0;
		all = 0;
		while (n--) {
			scanf("%d%d%d%d", &x, &y, &w, &h);
			all += (i64)w * h;
			r[m++] = (Rect){x, h};
			r[m++] = (Rect){x + w, -h};
		}
		sort(r, r + m, cmp);
		n = 0;
		cur = 0, sum = 0, now = -1;
		int ans = R;
		for (int i = 0; i <= R; ++i) {
			if (sum * 2 >= all) {
				if (now == -1) now = sum;
				if (now == sum) ans = i;
			}
			//printf("%d %d %lld %d %lld\n", i, ans, sum, cur, now); 
			while (n < m && r[n].x == i) cur += r[n++].len;
			sum += cur;
		}
		printf("%d\n", ans);
	}
	return 0;
}
