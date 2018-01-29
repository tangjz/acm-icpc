#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1001, mod = (int)1e9 + 7;
int n, pa, pb, pr, f[maxn][maxn];
int mod_inv(int x) {
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int F(int i, int j) { // f(i, j) = pa f(i, j + 1) + pb f(i + j, j)
	if(i >= n)
		return i;
	if(j == n) // f(i, j) = sum(pa^k pb f(i + j + k, j + k)) = 1/pb pb (i + j) + pa/pb^2 pb = i + j + pr
		return (i + j + pr) % mod;
	if(f[i][j] != -1)
		return f[i][j];
	return f[i][j] = ((LL)pa * F(i, j + 1) + (LL)pb * F(i + j, j)) % mod;
}
int main() {
	int x, y;
	scanf("%d%d%d", &n, &x, &y);
	pa = (LL)x * mod_inv(x + y) % mod;
	pb = (LL)y * mod_inv(x + y) % mod;
	pr = (LL)pa * mod_inv(pb) % mod;
	memset(f, -1, sizeof f);
	printf("%d\n", F(0, 1)); // f(0, 0) = f(0, 1)
	return 0;
}
