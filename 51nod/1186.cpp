#include <ctime>
#include <cstdio>
#include <cstdlib>
typedef double DB;
typedef long long LL;
typedef __int128_t int128;
const int maxl = 31, BLEN = 27, BMSK = (1 << BLEN) - 1, maxt = 21;
void read(int128 &x) {
	char buf[maxl];
	scanf("%s", buf);
	x = 0;
	for(int i = 0; buf[i]; ++i)
		x = (x << 3) + (x << 1) + (buf[i] - '0');
}
int rand30() {
	return RAND_MAX == 0x7FFF ? rand() << 15 | rand() : rand();
}
LL rand60() {
	return (LL)rand30() << 30 | rand30();
}
int128 rand120() {
	return (int128)rand60() << 60 | rand60();
}
int128 mod_mul(int128 x, int128 y, int128 p) {
	int128 ret = 0;
	for( ; y > 0; x = (x << BLEN) % p, y >>= BLEN)
		(y & BMSK) && (ret = (ret + x * (y & BMSK)) % p);
	return ret;
}
int mod_pow(int x, int y, int p) {
	int ret = 1;
	for( ; y > 0; x = (LL)x * x % p, y >>= 1)
		(y & 1) && (ret = (LL)ret * x % p);
	return ret;
}
int128 mod_pow(int128 x, int128 y, int128 p) {
	int128 ret = 1;
	for( ; y > 0; x = mod_mul(x, x, p), y >>= 1)
		(y & 1) && (ret = mod_mul(ret, x, p));
	return ret;
}
bool miller_rabin(int128 n) {
	if(n < 2 || !(n & 1))
		return n == 2;
	int s = 0;
	int128 r = n - 1;
	for( ; !(r & 1); ++s, r >>= 1);
	for(int i = 0; i < maxt; ++i) {
		int128 cur = mod_pow(rand120() % (n - 2) + 2, r, n), nxt;
		for(int j = 0; j < s; ++j) {
			nxt = mod_mul(cur, cur, n);
			if(nxt == 1 && cur != 1 && cur != n - 1)
				return 0;
			cur = nxt;
		}
		if(cur != 1)
			return 0;
	}
	return 1;
}
int main() {
	int128 n;
	srand(time(0));
	read(n);
	puts(miller_rabin(n) ? "Yes" : "No");
	return 0;
}
