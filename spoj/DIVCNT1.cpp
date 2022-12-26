#include <bits/stdc++.h>
typedef unsigned UL;
typedef unsigned long long ULL;
typedef __uint128_t BigInt;
UL iSqrt(ULL n) {
	UL x = (UL)floor(sqrtl(n));
	ULL y = (ULL)x * x;
	for( ; y > n; --x, y -= (ULL)x << 1 | 1);
	for( ; n - y >= ((ULL)x << 1 | 1); y += (ULL)x << 1 | 1, ++x);
	return x;
}
BigInt solve(ULL n) {
	UL ymax = iSqrt(n), ymin = (UL)floor(pow(n, 0.35));
	ULL x = n / ymax;
	UL y = n / x + 1;
	std::stack<std::pair<UL, UL> > stk;
	stk.push(std::make_pair(1, 0));
	stk.push(std::make_pair(1, 1));
	BigInt ret = 0;
	while(1) {
		UL dx = stk.top().first, dy = stk.top().second;
		stk.pop();
		for( ; (x + dx) * (y - dy) > n; x += dx, y -= dy)
			ret += x * dy + (((dy + 1ULL) * (dx - 1)) >> 1);
		if(y <= ymin)
			break;
		UL dx2 = dx, dy2 = dy;
		while(1) {
			dx = stk.top().first;
			dy = stk.top().second;
			if((x + dx) * (y - dy) > n)
				break;
			dx2 = dx;
			dy2 = dy;
			stk.pop();
		}
		while(1) {
			UL dx3 = dx + dx2, dy3 = dy + dy2;
			if((x + dx3) * (y - dy3) > n) { // go left
				dx = dx3;
				dy = dy3;
				stk.push(std::make_pair(dx, dy));
			} else { // go right
				ULL tp = x + dx3;
				if((BigInt)tp * (tp * dy) >= (BigInt)n * dx)
					break;
				dx2 = dx3;
				dy2 = dy3;
			}
		}
	}
	while(--y)
		ret += n / y;
	return (ret << 1) - (ULL)ymax * ymax;
}
void writeln(BigInt val) {
	static ULL BASE = (ULL)1e18;
	if(val < BASE) {
		printf("%llu\n", (ULL)val);
	} else {
		printf("%llu%018llu\n", (ULL)(val / BASE), (ULL)(val % BASE));
	}
}
int main() {
	int t;
	ULL n;
	scanf("%d", &t);
	while(t--) {
		scanf("%llu", &n);
		writeln(solve(n));
	}
	return 0;
}
