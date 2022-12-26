#include <cstdio>
typedef __uint128_t LL;
const int maxt = 2800;
LL n, m, v, x, y, a, b, c;
inline bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}
inline void read(LL &x) {
	register char ch;
	while(!isDigit(ch = getchar()));
	for(x = ch - '0'; isDigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch - '0'));
}
inline void write(LL x) {
	register int pos = 41;
	static char buf[41] = {};
	!x && (buf[--pos] = '0');
	for( ; x; buf[--pos] = '0' + (x % 10), x /= 10);
	puts(buf + pos);
}
inline LL mod_add(LL x, LL y) {
	return (x += y) < m ? x : x - m;
}
inline LL mod_mul(LL x, LL y) {
	if(x < y)
		return mod_mul(y, x);
	LL ret = 0;
	for( ; y; y >>= 1, x = mod_add(x, x))
		if(y & 1)
			ret = mod_add(ret, x);
	return ret;
}
int main() {
	for(int t = 0; t < maxt; ++t) {
		read(n);
		read(m);
		for(v = 1; v <= n; v <<= 1);
		for(x = 1, y = 0; (v >>= 1); ) {
			if(x != 1 || y != 0) {
				a = x;
				b = y;
				c = mod_mul(b, b);
				x = mod_add(mod_mul(a, a), c);
				y = mod_mul(a, b);
				y = mod_add(mod_add(y, y), c);
			}
			if(n & v) {
				c = mod_add(x, y);
				x = y;
				y = c;
			}
		}
		write(y);
	}
	return 0;
}
