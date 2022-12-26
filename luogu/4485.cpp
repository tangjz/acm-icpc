#include <bits/stdc++.h>
using namespace std;
typedef double DB;
typedef long long LL;
const DB pi = acos(-1);
const int maxLen = 17, maxs = 1 << maxLen | 1;
struct Complex {
	DB r, i;
	Complex() { r = i = 0; }
	Complex(DB r, DB i) : r(r), i(i) {}
	Complex operator + (Complex const &t) const { return Complex(r + t.r, i + t.i); }
	Complex operator - (Complex const &t) const { return Complex(r - t.r, i - t.i); }
	Complex operator * (Complex const &t) const { return Complex(r * t.r - i * t.i, r * t.i + i * t.r); }
} w[maxs], A[maxs], B[maxs];
void FFT(int len, Complex x[], int flag) {
	register int i, j, k;
	static int bitLen = 0;
	for(i = 1 << bitLen; i < len; ++bitLen, i <<= 1)
		for(j = 0, k = i; j < i; ++j, ++k)
			w[k] = k & 1 ? Complex(cos(pi / i * j), sin(pi / i * j)) : w[k >> 1];
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			swap(x[i], x[j]);
	}
	static Complex *W, t;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, W = w + i; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = W[k] * x[i + j + k];
				x[i + j + k] = x[j + k] - t;
				x[j + k] = x[j + k] + t;
			}
	if(flag == -1) {
		reverse(x + 1, x + len);
		for(i = 0; i < len; ++i) {
			x[i].r /= len;
			x[i].i /= len;
		}
	}
}
const int BLEN = 6, BASE = (int)1e6, BSFT = 10, BMSK = (1 << BSFT) - 1;
struct BigInt {
	vector<int> data;
	void clear() {
		if(!data.empty())
			vector<int>().swap(data);
	}
	void assign(LL x) {
		clear();
		for( ; x > 0; data.push_back(x % BASE), x /= BASE);
		if(data.empty())
			data.push_back(0);
		reverse(data.begin(), data.end());
	}
	void assign(const char buf[]) {
		clear();
		int len = strlen(buf);
		data.reserve((len - 1) / BLEN + 1);
		for(int i = len, j = i - BLEN; i > 0; i = j, j -= BLEN) {
			int val = 0;
			for(int k = max(j, 0); k < i; ++k)
				val = val * 10 + (buf[k] - '0');
			data.push_back(val);
		}
		reverse(data.begin(), data.end());
	}
	int length() const {
		return (int)data.size();
	}
	void show(char endc = '\n') const {
		int len = length();
		vector<int>::const_iterator it = data.begin();
		printf("%d", *(it++));
		for(int i = 1; i < len; ++i)
			printf("%0*d", BLEN, *(it++));
		if(endc)
			putchar(endc);
	}
	int compare(BigInt const &t) const {
		int len = length(), tlen = t.length();
		if(len != tlen)
			return len - tlen;
		vector<int>::const_iterator it = data.begin(), jt = t.data.begin();
		for(int i = 0; i < len; ++i) {
			int diff = *(it++) - *(jt++);
			if(diff)
				return diff;
		}
		return 0;
	}
	void operator <<= (int const &t) {
		if(t)
			data.resize(length() + t);
	}
	void operator >>= (int const &t) {
		int len = length() - t;
		if(len < 0) {
			assign(0LL);
		} else if(t) {
			data.resize(len);
		}
	}
	void addSelf() {
		int len = length(), rem = 0;
		vector<int>::reverse_iterator it = data.rbegin();
		for(int i = 0; i < len; ++i) {
			int &val = *(it++);
			rem += val << 1;
			val = rem % BASE;
			rem /= BASE;
		}
		if(rem)
			data.insert(data.begin(), rem);
	}
	void operator -= (BigInt const &t) {
		bool adt = 0;
		vector<int>::reverse_iterator it = data.rbegin();
		vector<int>::const_reverse_iterator jt = t.data.rbegin();
		while(jt != t.data.rend()) {
			int &val = *(it++);
			val -= *(jt++) + adt;
			if((adt = val < 0))
				val += BASE;
		}
		while(adt && it != data.rend()) {
			int &val = *(it++);
			if((adt = (--val) < 0))
				val += BASE;
		}
		if(length() > 1 && !data.front()) {
			vector<int>::iterator it = data.begin(), jt = data.begin() + 1;
			for( ; jt != data.end() && !(*jt); ++jt);
			if(jt == data.end()) {
				assign(0LL);
			} else {
				int dt = jt - it;
				while(jt != data.end())
					*(it++) = *(jt++);
				data.resize(length() - dt);
			}
		}
	}
	void operator *= (BigInt const &t) {
		int len = length();
		if(len == 1 && !data.front())
			return;
		int tlen = (int)t.length();
		if((tlen == 1 && !t.data.front())) {
			assign(0LL);
			return;
		}
		int plen;
		for(plen = 1; plen + 1 < len + tlen; plen <<= 1);
		vector<int>::const_reverse_iterator it = data.rbegin(), jt = t.data.rbegin();
		if((LL)len * tlen <= 8LL * plen * __builtin_ctz(plen)) {
			vector<int> tmp;
			tmp.resize(len + tlen);
			register int i, j;
			vector<int>::const_reverse_iterator it = data.rbegin(), jt;
			vector<int>::reverse_iterator kt;
			for(i = 0; i < len; ++i) {
				LL rem = 0, prd = *(it++);
				jt = t.data.rbegin();
				kt = tmp.rbegin() + i;
				for(j = 0; j < tlen; ++j) {
					int &val = *(kt++);
					rem += val + prd * *(jt++);
					val = rem % BASE;
					rem /= BASE;
				}
				if(rem)
					*(kt++) = rem;
			}
			data.assign(tmp.front() ? tmp.begin() : tmp.begin() + 1, tmp.end());
			return;
		}
		for(int i = 0, x; i < plen; ++i) {
			x = i < len ? *(it++) : 0;
			A[i] = x ? Complex(x & BMSK, x >> BSFT) : Complex();
			x = i < tlen ? *(jt++) : 0;
			B[i] = x ? Complex(x & BMSK, x >> BSFT) : Complex();
		}
		FFT(plen, A, 1);
		FFT(plen, B, 1);
		static Complex tp1, tp2;
		for(int i = 0; i + i <= plen; ++i) {
			int j = (plen - i) & (plen - 1);
			tp1 = Complex((A[i].r + A[j].r) / 2, (A[i].i - A[j].i) / 2);
			tp2 = Complex((A[i].i + A[j].i) / 2, (A[j].r - A[i].r) / 2);
			A[i] = tp1 * B[i];
			B[i] = tp2 * B[i];
			if(i != j) {
				tp1.i = -tp1.i;
				tp2.i = -tp2.i;
				A[j] = tp1 * B[j];
				B[j] = tp2 * B[j];
			}
		}
		FFT(plen, A, -1);
		FFT(plen, B, -1);
		len += tlen - 1;
		data.resize(len);
		LL rem = 0;
		vector<int>::reverse_iterator kt = data.rbegin();
		for(int i = 0; i < len; ++i) {
			LL vLL = A[i].r + 0.5, vLH = A[i].i + 0.5;
			LL vHL = B[i].r + 0.5, vHH = B[i].i + 0.5;
			LL tmp = (((vHH << BSFT) + vHL + vLH) << BSFT) + vLL;
			rem += tmp;
			*(kt++) = rem % BASE;
			rem /= BASE;
		}
		if(rem)
			data.insert(data.begin(), (int)rem);
	}
	void inverse(BigInt const &mod) {
		int mlen = mod.length(), plen;
		DB p = 0, q = BASE;
		vector<int>::const_iterator it = mod.data.begin();
		for(int i = 0; i < 3 && i < mlen; ++i) {
			p = p * BASE + *(it++);
			q *= BASE;
		}
		assign((LL)(q * BASE / p));
		for(plen = 1; plen <= mlen; plen <<= 1) {
			int qlen = (plen << 1) + 3, adt = min(mlen, qlen);
			static BigInt tmp;
			tmp.data.assign(mod.data.begin(), mod.data.begin() + adt);
			adt = qlen - adt;
			tmp *= *this;
			tmp >>= max(plen + 2 - adt, 0);
			adt -= min(plen + 2, adt);
			tmp *= *this;
			tmp >>= max(plen + 2 - adt, 0);
			addSelf();
			*this <<= plen;
			*this -= tmp;
		}
		*this >>= plen - (mlen + 1);
	}
	void modulo(BigInt const &mod, BigInt const &ivs) {
		if(compare(mod) < 0)
			return;
		int len = length(), mlen = mod.length();
		static BigInt tmp;
		tmp.data.assign(ivs.data.begin(), ivs.data.end());
		tmp >>= mlen + mlen - len;
		tmp *= *this;
		tmp >>= len + 2;
		tmp *= mod;
		if(compare(tmp) < 0)
			tmp -= mod;
		*this -= tmp;
		if(compare(mod) >= 0)
			*this -= mod;
	}
	LL toInteger() const {
		LL ret = 0;
		for(vector<int>::const_iterator it = data.begin(); it != data.end(); ++it)
			ret = ret * BASE + *it;
		return ret;
	}
} ;
const int maxn = (int)2e5 + 3;
BigInt mod, ivs, fct[maxn / 3];
struct Node {
	int idx;
	bool operator < (Node const &t) const {
		return fct[idx].compare(fct[t.idx]) > 0;
	}
};
priority_queue<Node> Q;
int main() {
	int n, k;
	static char buf[maxn];
	scanf("%d%d%s", &n, &k, buf);
	mod.assign(buf);
	bool isOne = mod.length() == 1 && mod.data.front() == 1;
	if(isOne || !n || k < n - 1 || (k == n && n <= 2)) {
		puts(!n && !isOne ? "1" : "0");
		return 0;
	}
	if(mod.length() <= 3) {
		LL rem = 1, mod = ::mod.toInteger();
		for(int i = 3; i < n; ++i) {
			LL res = 0;
			for(int j = i; j > 0; j >>= 1) {
				if(j & 1)
					(res += rem) >= mod && (res -= mod);
				(rem += rem) >= mod && (rem -= mod);
			}
			rem = res;
		}
		if(k == n) {
			LL res = 0;
			for(LL j = (n - 1LL) * (n - 2) / 2; j > 0; j >>= 1) {
				if(j & 1)
					(res += rem) >= mod && (res -= mod);
				(rem += rem) >= mod && (rem -= mod);
			}
			rem = res;
		} else {
			(rem += rem) >= mod && (rem -= mod);
		}
		printf("%lld\n", rem);
		return 0;
	}
	ivs.inverse(mod);
	const LL maxv = (LL)BASE * BASE * BASE - 1;
	int cnt = 0;
	LL prd = 1;
	for(int i = k < n ? 2 : 3; i < n; ++i) {
		if(prd > maxv / i) {
			fct[cnt].assign(prd);
			Q.push((Node){cnt++});
			prd = 1;
		}
		prd *= i;
	}
	for(int i = k < n ? n : n - 2; i < n; ++i) {
		int rem = i & 1 ? i : i >> 1;
		if(prd > maxv / rem) {
			fct[cnt].assign(prd);
			Q.push((Node){cnt++});
			prd = 1;
		}
		prd *= rem;
	}
	if(prd > 1) {
		fct[cnt].assign(prd);
		Q.push((Node){cnt++});
	}
	for( ; cnt > 1; --cnt) {
		int u = Q.top().idx;
		Q.pop();
		int v = Q.top().idx;
		Q.pop();
		fct[u] *= fct[v];
		fct[u].modulo(mod, ivs);
		Q.push((Node){u});
	}
	fct[Q.top().idx].show();
	return 0;
}
