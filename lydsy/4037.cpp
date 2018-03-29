#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 501, maxm = 5, maxd = 10, mod = 998244353;
int m;
char buf[maxn];
struct Matrix {
	int data[maxm][maxm];
	Matrix operator + (Matrix const &t) const {
		Matrix ret = *this;
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < m; ++j)
				(ret.data[i][j] += t.data[i][j]) >= mod && (ret.data[i][j] -= mod);
		return ret;
	}
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < m; ++j)
				for(int k = 0; k < m; ++k)
					ret.data[i][k] = (ret.data[i][k] + (LL)data[i][j] * t.data[j][k]) % mod;
		return ret;
	}
} A[maxd + 1][maxn], B, f[maxn];
int main() {
	scanf("%s%d", buf, &m);
	int len = strlen(buf);
	A[0][0].data[0][0] = A[1][0].data[0][0] = 1;
	for(int i = 1; i < m; ++i)
		A[0][0].data[i][i] = A[1][0].data[i][0] = A[1][0].data[i - 1][i] = 1;
	for(int i = 2; i < maxd; ++i)
		A[i][0] = A[i - 1][0] * A[1][0];
	for(int i = 1; i < len; ++i) {
		A[0][i] = A[0][i - 1];
		A[1][i] = A[maxd - 1][i - 1] * A[1][i - 1];
		for(int j = 2; j < maxd; ++j)
			A[j][i] = A[j - 1][i] * A[1][i];
	}
	f[0] = A[0][0];
	for(int i = 1; i <= len; ++i) {
		B = A[0][0];
		for(int j = i - 1; j >= 0; --j) {
			B = B * A[buf[j] - '0'][i - j - 1];
			f[i] = f[i] + f[j] * B;
		}
	}
	printf("%d\n", f[len].data[0][0]);
	return 0;
}
