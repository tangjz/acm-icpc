#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxs = (int)3e5 + 1, maxl = 127, BLEN = 30, BMSK = (1 << BLEN) - 1, maxd = maxs / BLEN + 1;
struct BigInt {
	int len, sta, data[maxd];
	void assign(int const &x) {
		len = 1;
		sta = 0;
		data[0] = x;
	}
	void assign(const char *buf) {
		int slen = strlen(buf);
		len = (slen - 1) / BLEN + 1;
		sta = 0;
		for(int i = 0, j = (slen - 1) % BLEN; i < slen; j += BLEN) {
			int &val = data[(slen - 1 - i) / BLEN] = 0;
			for( ; j >= 0; --j, ++i)
				val = val << 1 | (buf[i] == '1');
		}
	}
	int &get(int const &t) {
		return data[sta + t];
	}
	const int &get(int const &t) const {
		return data[sta + t];
	}
	void shiftRightOne() {
		if(len > 1) {
			--len;
			++sta;
		} else {
			assign(0);
		}
	}
	void operator += (BigInt const &t) {
		if(t.len == 1 && !t.get(0))
			return;
		for( ; len < t.len; get(len++) = 0);
		bool carry = 0;
		for(int i = 0; i < t.len; ++i) {
			int &cur = get(i) += carry + t.get(i);
			if((carry = cur > BMSK))
				cur &= BMSK;
		}
		for(int i = t.len; i < len && carry; ++i) {
			int &cur = get(i);
			if((carry = cur == BMSK)) {
				cur = 0;
			} else {
				++cur;
			}
		}
		if(carry)
			get(len++) = 1;
	}
	void operator *= (BigInt const &t) {
		if((len == 1 && !get(0)) || (t.len == 1 && !t.get(0))) {
			assign(0);
			return;
		}
		static int vlen, vec[maxd];
		vlen = len;
		memcpy(vec, data + sta, len * sizeof(int));
		len += t.len - 1;
		sta = 0;
		memset(data, 0, len * sizeof(int));
		for(int i = 0; i < t.len; ++i) {
			int *Data = data + i;
			ULL sum = 0, prd = t.get(i);
			for(int j = 0; j < vlen; ++j) {
				sum += Data[j] + prd * vec[j];
				Data[j] = sum & BMSK;
				sum >>= BLEN;
			}
			if(i == t.len - 1 && sum) {
				data[len++] = sum;
			} else {
				Data[vlen] += sum;
			}
		}
	}
} n, A, B, tmp, tA, tB;
int ans;
char buf[maxs];
int main() {
	scanf("%s", buf);
	n.assign(buf);
	A.assign(1);
	B.assign(0);
	while(1) {
		if(n.len == 1 || max(A.len, B.len) >= maxl - 5) {
			n *= A;
			n += B;
			A.assign(1);
			B.assign(0);
			if(n.len == 1)
				break;
		}
		tmp.assign(n.get(0));
		n.shiftRightOne();
		tmp *= A;
		B += tmp;
		tA.assign(1);
		tB.assign(B.get(0));
		B.shiftRightOne();
		for(int rem; (rem = tB.get(0)) > 0; ++ans) {
			tmp.assign(3);
			tA *= tmp;
			tB *= tmp;
			tmp.assign(rem & -rem);
			tB += tmp;
		}
		tB.shiftRightOne();
		A *= tA;
		B *= tA;
		B += tB;
		ans += BLEN;
	}
	for(ULL rem = n.get(0); rem != 1; ++ans)
		rem = rem & 1 ? rem * 3 + 1 : rem >> 1;
	printf("%d\n", ans);
	return 0;
}
