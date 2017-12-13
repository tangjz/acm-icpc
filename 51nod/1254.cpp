#include <stdio.h>
typedef long long LL;
const int maxn = 50001;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, a[maxn], cur, pre = 1;
LL f[2][2][2][3];
inline void clear(LL a[2][2][3]) {
	a[0][0][0] = a[0][0][1] = a[0][0][2] =
	a[0][1][0] = a[0][1][1] = a[0][1][2] =
	a[1][0][0] = a[1][0][1] = a[1][0][2] =
	a[1][1][0] = a[1][1][1] = a[1][1][2] = -INF;
}
inline void upd(LL &x, LL y) {
	x < y && (x = y);
}
int main() {
	scanf("%d", &n);
	clear(f[cur]);
	f[cur][0][0][0] = 0;
	for(int i = 0; i < n; ++i) {
		pre ^= 1;
		cur ^= 1;
		clear(f[cur]);
		int x;
		scanf("%d", &x);
		// left
		upd(f[cur][0][0][0], f[pre][0][0][0]);
		upd(f[cur][1][0][0], f[pre][0][0][0] + x);
		upd(f[cur][1][0][0], f[pre][1][0][0]);
		// middle
		upd(f[cur][0][0][1], f[pre][0][0][0] + x);
		upd(f[cur][0][0][1], f[pre][0][0][1] + x);
		upd(f[cur][0][1][1], f[pre][0][0][0]);
		upd(f[cur][0][1][1], f[pre][0][0][1]);
		upd(f[cur][0][1][1], f[pre][0][1][1] + x);
		upd(f[cur][1][0][1], f[pre][1][0][0] + x);
		upd(f[cur][1][0][1], f[pre][1][0][1] + x);
		upd(f[cur][1][1][1], f[pre][1][0][0]);
		upd(f[cur][1][1][1], f[pre][1][0][1]);
		upd(f[cur][1][1][1], f[pre][1][1][1] + x);
		// right
		upd(f[cur][0][0][2], f[pre][0][0][1]);
		upd(f[cur][0][0][2], f[pre][0][0][2]);
		upd(f[cur][1][0][2], f[pre][0][0][1] + x);
		upd(f[cur][1][0][2], f[pre][0][0][2] + x);
		upd(f[cur][1][0][2], f[pre][1][0][1]);
		upd(f[cur][1][0][2], f[pre][1][0][2]);
		upd(f[cur][0][1][2], f[pre][0][1][1]);
		upd(f[cur][0][1][2], f[pre][0][1][2]);
		upd(f[cur][1][1][2], f[pre][0][1][1] + x);
		upd(f[cur][1][1][2], f[pre][0][1][2] + x);
		upd(f[cur][1][1][2], f[pre][1][1][1]);
		upd(f[cur][1][1][2], f[pre][1][1][2]);
	}
	LL ans = -INF;
	upd(ans, f[cur][0][0][1]);
	upd(ans, f[cur][0][0][2]);
	upd(ans, f[cur][1][1][1]);
	upd(ans, f[cur][1][1][2]);
	printf("%lld\n", ans);
	return 0;
}
