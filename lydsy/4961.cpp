#include <map>
#include <cstdio>
#include <algorithm>
namespace fastIO {
	const int BUF_SIZE = 100001;
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	template<class T> inline void read(T& x) {
		char ch;
		while(blank(ch = nc()));
		if(!IOerror)
			for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
	}
}
namespace int128_t {
	typedef unsigned long long ULL;
	const int BLEN = 40;
	const ULL BASE = (1ULL << BLEN) - 1; // [0, BASE]
	struct BigInt {
		ULL upp, low;
		BigInt() : upp(0), low(0) {}
		BigInt(int _low) : upp(0), low(_low) {}
		BigInt(ULL _upp, ULL _low) : upp(_upp), low(_low) {}
		bool operator < (BigInt const &t) const {
			return upp < t.upp || (upp == t.upp && low < t.low);
		}
		bool operator == (BigInt const &t) const {
			return upp == t.upp && low == t.low;
		}
		BigInt operator + (BigInt const &t) const {
			BigInt ret = (BigInt){upp + t.upp, low + t.low};
			if(ret.low > BASE) {
				++ret.upp;
				ret.low &= BASE;
			}
			return ret;
		}
		BigInt operator << (int const &t) const { // t = 1, 3
			BigInt ret = (BigInt){upp << t, low << t};
			if(ret.low > BASE) {
				ret.upp += ret.low >> BLEN;
				ret.low &= BASE;
			}
			return ret;
		}
		void operator *= (int const &t) { // t <= 61
			ULL res = low * t;
			low = res & BASE;
			upp = upp * t + (res >> BLEN);
		}
		BigInt operator / (int const &t) const { // t <= 61
			ULL res = (upp % t) << BLEN | low;
			return (BigInt){upp / t, res / t};
		}
		void operator /= (int const &t) { // t <= 10^6
			ULL res = (upp % t) << BLEN | low;
			upp /= t;
			low = res / t;
		}
		int operator % (int const &t) const {
			return (int)(((upp % t) << BLEN | low) % t);
		}
	};
}
using int128_t::BigInt;
typedef long long LL;
const int maxm = 19, pr[maxm] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
const int maxe = 80, maxs = 172513, maxv = 1290241, mod = (int)1e9 + 7;
int tot, inv[maxv], sz, p[maxm], e[maxm], f[maxs], g[maxs][maxm];
std::map<BigInt, int> Hash;
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int dfs(BigInt val, int sig) {
	if(Hash.count(val))
		return Hash[val];
	int cID = Hash[val] = tot++, pID, sum = 0;
	for(int i = 0, k = sz, j = k - 1; i < sz; ++i, --j) {
		if(e[j] != e[k]) {
			k = j;
			int nsig = sig - sig / (e[k] + 1);
			sz -= !(--e[k]);
			pID = dfs(val / pr[k], nsig);
			sz += !(e[k]++);
		}
		int o = i - (e[k] == 1);
		mod_inc(sum, o < 0 ? f[pID] : g[pID][o]);
		g[cID][i] = sum;
	}
	f[cID] = (LL)(sig + sum) * inv[sig - 1] % mod;
	for(int i = 0; i < sz; ++i)
		mod_inc(g[cID][i], f[cID]);
	return cID;
}
int main() {
	inv[1] = 1;
	for(int i = 2; i < maxv; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	Hash[1] = tot++;
	BigInt val;
	for(int Case = 1; fastIO::read(val), fastIO::read(sz), !fastIO::IOerror; ++Case) {
		for(int i = 0; i < sz; ++i)
			fastIO::read(p[i]);
		int sig = 1;
		for(int i = 0; i < sz; ++i) {
			for(e[i] = 0; val % p[i] == 0; ++e[i], val /= p[i]);
			sig *= e[i] + 1;
		}
		e[sz] = 0;
		std::sort(e, e + sz, std::greater<int>());
		for(int i = 0; i < sz; ++i)
			for(int j = 0; j < e[i]; ++j)
				val *= pr[i];
		printf("%d\n", f[dfs(val, sig)]);
	}
	return 0;
}