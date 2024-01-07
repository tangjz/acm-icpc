/*
 * 矩阵递推 + 费马小定理
 */
#include <cstdio>
typedef long long LL;
const int maxn = 1000010;
const LL mod = 1000000007;
char n[maxn], m[maxn];
LL a, b, c, d, nlen, mlen;
void init1(LL &len,char*ch){for(int i(0);ch[i];++i)len=((len<<3)+(len<<1)+ch[i]-'0')%mod;len=((len-1)%mod+mod)%mod;}
void init2(LL &len,char*ch){for(int i(0);ch[i];++i)len=((len<<3)+(len<<1)+ch[i]-'0')%(mod-1);len=((len-1)%(mod-1)+(mod-1))%(mod-1);}
struct Matrix { LL a, b; void operator*=(const Matrix&x){this->b=(b*x.a+x.b)%mod;this->a=a*x.a%mod;} } A, B, SA, SB;
int main()
{
	scanf("%s%s%lld%lld%lld%lld", n, m, &a, &b, &c, &d);
	a == 1ll ? init1(nlen, n) : init2(nlen, n);
	c == 1ll ? init1(mlen, m) : init2(mlen, m);
	A = (Matrix){a, b}, B = (Matrix){c, d}, SA = SB = (Matrix){1, 0};
	while(mlen) { if(mlen & 1) SA *= A; A *= A; mlen >>= 1; }
	B *= SA;
	while(nlen) { if(nlen & 1) SB *= B; B *= B; nlen >>= 1; }
	SA *= SB;
	printf("%lld\n", (SA.a + SA.b) % mod);
}
