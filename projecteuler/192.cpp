#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int BASE = (int)1e8;
struct BigInt {
	int len, num[11];
	BigInt() { len = 0; }
	BigInt(LL x) {
		for(len = 0; x; num[len++] = x % BASE, x /= BASE);
	}
	bool operator < (BigInt const &t) const {
		if(len != t.len)
			return len < t.len;
		for(int i = len - 1; i >= 0; --i)
			if(num[i] != t.num[i])
				return num[i] < t.num[i];
		return 0;
	}
	BigInt operator + (BigInt const &t) const {
		BigInt ret = {};
		ret.len = max(len, t.len);
		int tmp = 0;
		for(int i = 0; i < ret.len; ++i) {
			if(i < len)
				tmp += num[i];
			if(i < t.len)
				tmp += t.num[i];
			ret.num[i] = tmp % BASE;
			tmp /= BASE;
		}
		for( ; tmp; ret.num[ret.len++] = tmp % BASE, tmp /= BASE);
		return ret;
	}
	BigInt operator * (BigInt const &t) const {
		BigInt ret = {};
		ret.len = len + t.len - 1;
		LL tmp = 0;
		for(int i = 0; i < ret.len; ++i) {
			for(int j = 0; j <= i && j < len; ++j)
				if(i - j < t.len)
					tmp += (LL)num[j] * t.num[i - j];
			ret.num[i] = tmp % BASE;
			tmp /= BASE;
		}
		for( ; tmp; ret.num[ret.len++] = tmp % BASE, tmp /= BASE);
		return ret;
	}
};
LL solve(int val, LL &xL, LL &yL, LL &xR, LL &yR, LL yLim) {
	for(LL xM = xL + xR, yM = yL + yR; yM <= yLim; xM = xL + xR, yM = yL + yR) {
		if((__int128_t)xM * xM <= (__int128_t)yM * yM * val) {
			LL L = 1, R = (yLim - yL) / yR;
			while(L < R) {
				LL M = (L + R + 1) >> 1;
				xM = xL + M * xR;
				yM = yL + M * yR;
				if((__int128_t)xM * xM <= (__int128_t)yM * yM * val)
					L = M;
				else
					R = M - 1;
			}
			xL += L * xR;
			yL += L * yR;
		} else {
			LL L = 1, R = (yLim - yR) / yL;
			while(L < R) {
				LL M = (L + R + 1) >> 1;
				xM = xR + M * xL;
				yM = yR + M * yL;
				if((__int128_t)xM * xM > (__int128_t)yM * yM * val)
					L = M;
				else
					R = M - 1;
			}
			xR += L * xL;
			yR += L * yL;
		}
	}
	BigInt fz = BigInt(xL) * BigInt(yR) + BigInt(xR) * BigInt(yL), fm = BigInt(yL) * BigInt(yR);
	return fm * fm * BigInt(4LL * val) < fz * fz ? yL : yR;
}
int main() {
	{
		LL xL = 3LL, yL = 1LL, xR = 4LL, yR = 1LL;
		printf("%lld\n", solve(13, xL, yL, xR, yR, 20LL));
		printf("%lld/%lld %lld/%lld\n", xL, yL, xR, yR);
	}
	{
		LL xL = 3LL, yL = 1LL, xR = 4LL, yR = 1LL;
		printf("%lld\n", solve(13, xL, yL, xR, yR, 30LL));
		printf("%lld/%lld %lld/%lld\n", xL, yL, xR, yR);
	}
	LL ans = 0;
	for(int i = 1, j = 1; i <= 100000; ++i) {
		if(i == j * j) {
			++j;
			continue;
		}
		LL xL = j - 1, yL = 1LL, xR = j, yR = 1LL;
		ans += solve(i, xL, yL, xR, yR, (LL)1e12);
	}
	printf("%lld\n", ans);
	return 0;
}
