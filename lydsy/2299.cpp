/*
 * 分类讨论
 */
#include <cstdio>
typedef long long LL;
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }
int main() {
	int t; LL a, b, x, y, z;
	for(scanf("%d", &t); t--; ) {
		scanf("%lld%lld%lld%lld", &a, &b, &x, &y);
		if(!a && !b) { puts(!x && !y ? "Y" : "N"); continue; }
		z = gcd(a, b) << 1;
		puts((x % z == 0 && y % z == 0) || ((x - a) % z == 0 && (y - b) % z == 0) || ((x - b) % z == 0 && (y - a) % z == 0) || ((x - a - b) % z == 0 && (y - a - b) % z == 0) ? "Y" : "N");
    }
}
