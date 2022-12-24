#include <stdio.h>
inline long long solve1(int n, int m, int x, int y) {
	long long pre = 0, cnt = 1;
	while(!(!n && !m))
		if(n == m) {
			cnt <<= 1;
			if((x >> (n - 1)) & 1) {
				x = (1 << n) - 1 - x;
				pre = cnt - 1 - pre;
			}
			--n;
		} else {
			cnt <<= 1;
			if((y >> (m - 1)) & 1) {
				y = (1 << m) - 1 - y;
				pre = cnt - 1 - pre;
			}
			--m;
		}
	return pre;
}
inline long long solve2(int n, int m, int xk, int yk, long long pre) {
	int x = 0, y = 0;
	for(int xk = 0, yk = 0; !(xk == n && yk == m); ) {
		bool flip = (pre >> (n - xk + m - yk - 1)) & 1;
		if(flip)
			pre = (1LL << (n - xk + m - yk)) - 1 - pre;
		if(xk == yk) {
			++yk;
			if(flip)
				y = (1 << yk) - 1 - y;
		} else {
			++xk;
			if(flip)
				x = (1 << xk) - 1 - x;
		}
	}
	return (long long)x << m | y;
}
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int typ, len;
		long long num;
		scanf("%d%d%lld", &typ, &len, &num);
		--num;
		if(typ == 1) {
			printf("%lld\n", solve1(len, len, num >> len, num & ((1 << len) - 1)) + 1);
		} else {
			printf("%lld\n", solve2(len, len, 0, 0, num) + 1);
		}
	}
	return 0;
}
