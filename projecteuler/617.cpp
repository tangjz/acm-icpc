#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxm = (int)1e7 + 1;
const LL maxn = (LL)1e18 + 1;
const double eps = 1e-9;
LL ipow(LL x, int k) {
	LL ret = 1;
	for( ; k > 0; x *= x, k >>= 1)
		(k & 1) && (ret *= x);
	return ret;
}
LL iroot(LL x, int k) {
	LL ret = (int)pow(x, 1.0 / k);
	for( ; pow(ret, k) < maxn && ipow(ret, k) <= x; ++ret);
	for( ; pow(ret, k) >= maxn || ipow(ret, k) > x; --ret);
	return ret;
}
int m;
struct Triple {
	LL n, e, num;
	bool operator == (Triple const &t) const {
		return n == t.n && e == t.e && num == t.num;
	}
	bool operator < (Triple const &t) const {
		if(n != t.n)
			return n < t.n;
		if(e != t.e)
			return e < t.e;
		return num < t.num;
	}
} seq[maxm];
int solve(LL lim) {
	int ret = (int)(sqrtl(lim + 0.25) - 0.5);
	for( ; (LL)ret * (ret + 1) <= lim; ++ret);
	for( ; (LL)ret * (ret + 1) > lim; --ret);
	ret -= ret > 1;
	set<Triple> Hash;
	m = 0;
	for(int pp = 2; pow(pp, 4) <= lim + eps; ++pp) {
		LL num = ipow(pp, 2), n = num * (num + 1);
		if(n > lim)
			break;
		seq[m] = (Triple){n, 2, num};
		if(!Hash.count(seq[m]))
			Hash.insert(seq[m++]);
	}
	for(int e = 3; e < 60; ++e)
		for(int num = 2; pow(num, e) <= lim + eps; ++num) {
			LL n = ipow(num, e) + num;
			if(n > lim)
				break;
			seq[m] = (Triple){n, e, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		}
	for(int i = 0; i < m; ++i) {
		LL rt = iroot(seq[i].num, seq[i].e);
		if(ipow(rt, seq[i].e) == seq[i].num) {
			seq[m] = (Triple){seq[i].n, seq[i].e, rt};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		}
	}
	for(int i = 0; i < m; ++i) {
		LL n = seq[i].n, e = seq[i].e, num = seq[i].num;
		if(e == 2) {
			if(num * (num + 1) == n)
				--ret;
		} else if(e == 4) {
			seq[m] = (Triple){n, 2, ipow(num, 2)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		} else if(e == 8) {
			seq[m] = (Triple){n, 2, ipow(num, 4)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, ipow(num, 2)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		} else if(e == 9) {
			seq[m] = (Triple){n, 3, ipow(num, 3)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 3, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		} else if(e == 16) {
			seq[m] = (Triple){n, 2, ipow(num, 8)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, ipow(num, 4)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, ipow(num, 2)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 4, ipow(num, 4)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 4, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		} else if(e == 25) {
			seq[m] = (Triple){n, 5, ipow(num, 5)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 5, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		} else if(e == 27) {
			seq[m] = (Triple){n, 3, ipow(num, 9)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 3, ipow(num, 3)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 3, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		} else if(e == 32) {
			seq[m] = (Triple){n, 2, ipow(num, 16)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, ipow(num, 8)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, ipow(num, 4)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, ipow(num, 2)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 2, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		} else if(e == 36) {
			seq[m] = (Triple){n, 6, ipow(num, 6)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 6, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		} else if(e == 49) {
			seq[m] = (Triple){n, 7, ipow(num, 7)};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
			seq[m] = (Triple){n, 7, num};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		}
	}
	for(int i = 0; i < m; ++i) {
		LL rt = iroot(seq[i].num, seq[i].e);
		if(ipow(rt, seq[i].e) == seq[i].num) {
			seq[m] = (Triple){seq[i].n, seq[i].e, rt};
			if(!Hash.count(seq[m]))
				Hash.insert(seq[m++]);
		}
	}
//	sort(seq, seq + m); 
//	for(int i = 0; i < m; ++i)
//		printf("%lld %lld %lld\n", seq[i].n, seq[i].e, seq[i].num);
	return ret + m;
}
int main() {
	printf("ways %d: %d\n", 10, solve(10));
	printf("ways %d: %d\n", 100, solve(100));
	printf("ways %d: %d\n", 1000, solve(1000));
	printf("ways %d: %d\n", 1000000, solve(1000000));
	printf("ways %lld: %d\n", (LL)1e12, solve((LL)1e12));
	printf("ways %lld: %d\n", (LL)1e18, solve((LL)1e18));
	return 0;
}
