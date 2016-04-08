/*
 * 矩阵递推 + 十进制快速幂
 * PS: 当然也可以直接模p^2-1 这是所有斐波那契数列的循环节 
 */ 
#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 1000010;
const LL mod = 2012182013;
struct Matrix {
	LL a, b, c, d, e, f;
	Matrix operator * (const Matrix &x) const {
		Matrix t;
		t.a = (a * x.a + d * x.b) % mod; t.d = (a * x.d + d * x.e) % mod;
		t.b = (b * x.a + e * x.b) % mod; t.e = (b * x.d + e * x.e) % mod;
		t.c = (c * x.a + f * x.b + x.c) % mod; t.f = (c * x.d + f * x.e + x.f) % mod;
		return t;
	}
	void operator *= (const Matrix &x) { *this = *this * x; }
	Matrix pow10() const { Matrix t, s = *this; s *= s; t = s; s *= s; s *= s; return s * t; }
} A[11], B[11], SA, SB;
LL a, b, c, d, e, f;
char n[maxn], m[maxn], tmp[maxn];
inline void scan(LL &x) { scanf("%s", tmp); x = 0; for(int i = 0; tmp[i]; ++i) x = ((x << 3) + (x << 1) + tmp[i] - '0') % mod; }
int main() {
	scanf("%s%s", n, m); scan(a); scan(b); scan(c); scan(d); scan(e); scan(f);
	int i, nlen = strlen(n), mlen = strlen(m);
	for(i = nlen - 1, --n[i]; i >= 0; n[i--] -= '0') if(n[i] < '0') --n[i - 1], n[i] += 10;
	for(i = mlen - 1, m[i] -= 2; i >= 0; m[i--] -= '0') if(m[i] < '0') --m[i - 1], m[i] += 10;
	A[0] = B[0] = SA = SB = {1, 0, 0, 0, 1, 0};
	A[1] = {0, 1, 0, a, b, c};
	for(i = 2; i < 10; ++i) A[i] = A[1] * A[i - 1];
	for(i = 0; i < mlen; ++i) SA = SA.pow10() * A[(int)m[i]];
	B[1] = {0, 1, 0, d, e, f};
	B[1] *= B[1] * SA;
	for(i = 2; i < 10; ++i) B[i] = B[1] * B[i - 1];
	for(i = 0; i < nlen; ++i) SB = SB.pow10() * B[(int)n[i]];
	SA *= SB;
	printf("%lld\n", (SA.d + SA.e + SA.f) % mod);
}
