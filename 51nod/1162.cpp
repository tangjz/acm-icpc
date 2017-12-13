#include <ctime>
#include <cmath>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef double DB;
typedef long long LL;
typedef __int128_t int128;
const int maxl = 31, maxe = 97, maxs = 9; // input length, output size
const int maxp = (int)5e4 + 1; // euler sieve size
const int BLEN = 30, BMSK = (1 << BLEN) - 1; // quick multiplication
const int maxt = 21; // miller rabin test times
const LL maxv = (LL)1e18 + 1; // pollard's rho bound
const int maxn = 2001, maxm = (int)1.5e7 + 1, maxq = maxn + 50; // prime base size, candidate size
void read(int128 &x) {
	char buf[maxl];
	scanf("%s", buf);
	x = 0;
	for(int i = 0; buf[i]; ++i)
		x = (x << 3) + (x << 1) + (buf[i] - '0');
}
void write(int128 x, char endc = '\0') {
	char buf[maxl], *ptr = buf;
	for( ; x > 0; x /= 10)
		*ptr++ = '0' + (int)(x % 10);
	if(buf == ptr)
		*ptr++ = '0';
	reverse(buf, ptr);
	*ptr = '\0';
	printf("%s", buf);
	if(endc)
		putchar(endc);
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
	if(x < y)
		swap(x, y);
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
bool miller_rabin(int128 n) { // n is odd, n >= maxp
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
LL pollard_rho(LL n) { // n is compromised, maxp <= n < maxv
	LL x = rand60() % n, y = x, c = rand60() % n, r;
	for(LL i = 1, k = 2; ; ++i) {
		if(i == k) {
			y = x;
			k <<= 1;
		}
		(x = mod_mul(x, x, n) + c) >= n && (x -= n);
		if((r = __gcd(abs(x - y), n)) > 1)
			return r;
	}
	return n;
}
int ptot, pr[maxp], qtot, qr[maxn], stot;
DB seq[maxm]; // int128 seq[maxm];
LL num[maxq];
bitset<maxn> msk[maxq], ex[maxq];
bitset<maxq> sel[maxq];
int128 quadratic_sieve(int128 n) {
	qtot = 0;
	for(int i = 0; i < ptot && qtot < maxn; ++i)
		if(pr[i] == 2 || mod_pow((int)(n % pr[i]), (pr[i] - 1) >> 1, pr[i]) == 1)
			qr[qtot++] = pr[i];
	LL sqn = (LL)sqrt((DB)n);
	for( ; (int128)sqn * sqn <= n; ++sqn);
	seq[0] = (int128)sqn * sqn - n;
	for(int i = 0; i < maxm; ++i)
		seq[i + 1] = seq[i] + ((sqn + i) << 1 | 1);
	for(int i = 0; i < qtot; ++i) {
		int pp = qr[i], rem = ((int128)sqn * sqn - n) % pp, sq = sqn % pp;
		for(int j = 0; j < pp; ++j) {
			if(!rem)
				for(int k = j; k < maxm; k += pp)
					seq[k] /= pp; // for(seq[k] /= pp; seq[k] % pp == 0; seq[k] /= pp);
			rem = (rem + ((sq + j) << 1 | 1)) % pp;
		}
	}
	stot = 0;
	int128 cur = (int128)sqn * sqn - n;
	for(int i = 0; i < maxm && stot < maxq; ++i) {
		if(fabs(seq[i] - 1) <= 1e-9) { // if(seq[i] == 1) {
			int128 tmp = cur;
			for(int j = 0; j < qtot; ++j)
				if(tmp % qr[j] == 0) {
					ex[stot][j] = msk[stot][j] = 1;
					tmp /= qr[j];
				}
			sel[stot].reset();
			sel[stot].set(stot);
			num[stot++] = sqn + i;
		}
		cur += (sqn + i) << 1 | 1;
	}
	int rk = 0;
	for(int i = 0; i < qtot; ++i) {
		int k = -1;
		for(int j = rk; j < stot; ++j)
			if(msk[j][i]) {
				k = j;
				break;
			}
		if(k == -1)
			continue;
		swap(msk[rk], msk[k]);
		swap(sel[rk], sel[k]);
		for(int j = 0; j < stot; ++j)
			if(j != rk && msk[j][i]) {
				msk[j] ^= msk[rk];
				sel[j] ^= sel[rk];
			}
		++rk;
	}
	for(int i = rk; i < stot; ++i) {
		int128 x = 1, y = 1;
		static int cnt[maxn];
		memset(cnt, 0, sizeof cnt);
		for(int j = 0; j < stot; ++j)
			if(sel[i][j]) {
				x = mod_mul(x, num[j], n);
				for(int k = 0; k < qtot; ++k)
					cnt[k] += ex[j][k];
			}
		for(int j = 0; j < qtot; ++j)
			y = mod_mul(y, mod_pow((int128)qr[j], (int128)(cnt[j] >> 1), n), n);
		int128 u = __gcd(x + y < n ? x + y : x + y - n, n);
		if(1 < u && u < n)
			return u;
		int128 v = __gcd(x - y < 0 ? x - y + n : x - y, n);
		if(1 < v && v < n)
			return v;
	}
	return n;
}
void factorize(int128 &n, int &tot, int128 fct[]) {
	int L = 0, R = 0;
	int128 que[maxs];
	que[R++] = n;
	while(L < R) {
		int128 &u = que[L++];
		if(u == 1)
			continue;
		if(miller_rabin(u)) {
			n /= u;
			fct[tot++] = u;
			for(int i = L; i < R; ++i)
				while(que[i] % u == 0) {
					que[i] /= u;
					fct[tot++] = u;
				}
		} else if(u <= maxv) { // pollard rho
			LL v;
			while((v = pollard_rho(u)) == u);
			que[R++] = v;
			que[R++] = u / v;
		} else { // quadratic sieve
			int128 v = quadratic_sieve(u);
			if(u == v) {
				puts("error!");
			}
			que[R++] = v;
			que[R++] = u / v;
		}
	}
}
void euler_sieve(int128 &n, int &tot, int128 fct[]) {
	static int d[maxp] = {};
	for(int i = 2; i < maxp && i <= n; ++i) {
		if(!d[i]) {
			pr[ptot++] = d[i] = i;
			for( ; n % i == 0; n /= i, fct[tot++] = i);
		}
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
}
int main() {
	srand(time(0));
	int tot = 0;
	int128 n, fct[maxe];
	read(n);
	euler_sieve(n, tot, fct); // after that, remain factors >= maxp
	factorize(n, tot, fct);
	sort(fct, fct + tot);
	for(int i = 0; i < tot; ++i)
		write(fct[i], " \n"[i == tot - 1]);
	if(n > 1)
		write(n, '\n');
	return 0;
}
