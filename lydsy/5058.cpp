#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1, maxd = 4, mod = (int)1e9 + 7;
struct Matrix {
	int data[maxd + 1][maxd + 1];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 0; i < maxd; ++i)
			for(int j = 0; j < maxd; ++j)
				for(int k = 0; k < maxd; ++k)
					ret.data[i][k] = (ret.data[i][k] + (LL)data[i][j] * t.data[j][k]) % mod;
		return ret;
	}
} A, B;
int n, m, coeff[maxd + 1], bit[2][maxn];
int main() {
	scanf("%d%d", &n, &m);
	A.data[0][0] = A.data[1][1] = A.data[2][2] = A.data[3][3] = B.data[2][1] = 1;
	B.data[2][0] = mod - 1;
	B.data[0][0] = B.data[1][1] = (n * (n - 3LL) / 2 + mod) % mod;
	B.data[2][2] = (n * (n - 5LL) / 2 + mod) % mod;
	B.data[0][3] = B.data[1][3] = B.data[3][3] = n * (n - 1LL) / 2 % mod;
	B.data[2][3] = n;
	for( ; m > 0; m >>= 1, B = B * B)
		if(m & 1)
			A = A * B;
	memcpy(coeff, A.data[2], maxd * sizeof(int));
	int ans = 0, cnt = 0, sum = 0;
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		int lcnt = 0, lsum = 0;
		for(int j = x - 1; j > 0; j -= j & -j) {
			lcnt += bit[0][j];
			(lsum += bit[1][j]) >= mod && (lsum -= mod);
		}
		ans = (ans + coeff[0] * ((LL)lcnt * i % mod + sum - lsum)
			+ coeff[1] * (lsum + (LL)(cnt - lcnt) * i % mod)
			+ (LL)coeff[2] * (cnt - lcnt)
			+ (LL)coeff[3] * cnt) % mod;
		++cnt;
		(sum += i) >= mod && (sum -= mod);
		for(int j = x; j <= n; j += j & -j) {
			++bit[0][j];
			(bit[1][j] += i) >= mod && (bit[1][j] -= mod);
		}
	}
	printf("%d\n", ans < 0 ? ans + mod : ans);
	return 0;
}
